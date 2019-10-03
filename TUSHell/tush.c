/**
 * TUSHell
 * @author: Ryan Jones
 * Created for COS 421 - Operating Systems with Dr. Geisler
 *
 * I Would like to thank Dr. Geisler for all of the time and
 * grace he extended to me by helping me with this project.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef int bool;
#define true 1
#define false 0
#define ARG_MAX 2097152

int num_procs = 0;
int num_words = 0;


void handle_sigchld(int signal) {
    int s;
    for(int i=0; i<num_procs; i++) {
        waitpid(-1, &s, WNOHANG);
        if(WIFEXITED(s)) {
            num_procs--;
        }
    }
}


void print_working_directory() {
    char cwd[PATH_MAX];
    if(getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    }
    if(errno) {
        fprintf(stderr, "%s\n", strerror(errno));
    }
}


void change_directory(char *new_dir) {
    new_dir = strtok(new_dir, "cd ");
    chdir(new_dir);
    if(errno) {
        fprintf(stderr, "%s\n", strerror(errno));
    }
}


int count_words(char *str) {
    int i = 0;
    char *token = strtok(str, " ");
    while(token != NULL) {
        i++;
        token = strtok(NULL, " ");
    }
    return i;
}


void run_program(char **command, char *input, char *output, char **envp) {
    bool has_path = false;
    if (!strncmp(command[0], "/", 1) || !strncmp(command[0], "./", 2) || !strncmp(command[0], "../", 3)) has_path = true;
    if(input != NULL) {
        close(0);
        open(input, 0, O_RDONLY);
        if(errno) {
            fprintf(stderr, "%s\n", strerror(errno));
        }
    }
    if(output != NULL) {
        close(1);
        open(output, O_CREAT|O_RDWR, S_IRWXU);
        if(errno) {
            fprintf(stderr, "%s\n", strerror(errno));
        }
    }
    if(has_path) {
        execve(command[0], command, envp);
    } else {
        char cur_dir[strlen(command[0]) + 2];
        strcpy(cur_dir, "./");
        strcpy(cur_dir, command[0]);
        execv(cur_dir, command);
        if(errno == ENOENT) {
            char local[strlen(getenv("PATH"))];
            strcpy(local, getenv("PATH"));
            char *file = command[0];
            char *token = strtok(local, ":");
            while(token != NULL) {
                char copy[strlen(token)+strlen(file)+1];
                strcpy(copy, token);
                strcat(copy, "/");
                strcat(copy, file);
                execve(copy, command, envp);
                token = strtok(NULL, ":");
            }
        }
    }
    if(errno) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(1);
    }
}


bool has_pipe(char *str) {
    return(strchr(str, '|') != NULL);
}


char **break_down_string(char *str) {
    char test[strlen(str)];
    char other[strlen(str)];
    strcpy(other, str);
    strcpy(test, str);
    int spaces = count_words(test);
    char **c_list = malloc(spaces * sizeof(char *));
    char *token = strtok(other, "|");
    int place = 0;
    int i = 0;
    int start = 0;
    char token_char = ' ';

    while(token[i] != '\0' && token[i] != '\n') {
        if(token[i]=='\'') {
            if(token_char=='\'') {
                token_char = ' ';
                i++;
                continue;
            } else {
                token_char = '\'';
            }
        } else if(token[i]=='\"') {
            if(token_char=='\"') {
                token_char = ' ';
                i++;
                continue;
            } else {
                token_char = '\"';
            }
        }
        if(token[i]!=token_char) {
            start = i;
            while(token[i] != token_char && token[i] != '\0') {
                i++;
            }
            char s[i-start];
            for(int j = 0; j < i-start; j++) {
                s[j] = token[start+j];
            }
            s[i-start] = '\0';
            c_list[place] = malloc(sizeof(s));
            strcpy(c_list[place], s);
            place++;
        } else {
            i++;
        }
    }
    c_list[place] = '\0';
    return c_list;
}


void tokenize(char *str, char **envp) {
    int fd[2];
    char other[strlen(str)];
    strcpy(other, str);

    char *token;
    token = strtok(other, "|");

    char *input;
    char *output;
    if(input != NULL) input = NULL;
    if(output != NULL) output = NULL;
    char *has_output = strchr(token, '>');
    char *has_input = strchr(token, '<');
    if(has_output != NULL) {
        output = strtok(has_output, "> \n");
        token = strtok(token, ">");
    }
    if(has_input != NULL) {
        input = strtok(has_input, "< \n");
        token = strtok(token, "<");
    }

    if(has_pipe(str)) {
        pipe(fd);
        int f = fork();
        if(f < 0) {
            fprintf(stderr, "Problem with fork(), exiting...\n");
            exit(1);
        } else if(f) {
            dup2(fd[0], 0);
            close(fd[1]);
            close(fd[0]);
            tokenize(strchr(str, '|')+2, envp);
        } else {
            dup2(fd[1], 1);
            close(fd[0]);
            close(fd[1]);
            run_program(break_down_string(token), input, output, envp);
        }
    } else {
        run_program(break_down_string(token), input, output, envp);
    }
}


void version() {
    printf("JONES Shell, Version 1.8\n");
    printf("Copyright (C) 2019 Ryan Jones Software [tm]\n");
    printf("Unlicensed product, use at your own risk.\n");
}


int main(int argc, char **argv, char **envp) {
    signal(SIGCHLD, handle_sigchld);
    char input[ARG_MAX];
    while(1) {
        printf("$ ");
        fgets(input, ARG_MAX, stdin);
        char *msg = strtok(input, "\n");
        if(msg == NULL) continue;
        if      (!strcmp(msg, "exit"))      break;
        else if (!strcmp(msg, "version"))   version();
        else if (!strcmp(msg, "pwd"))       print_working_directory();
        else if (!strncmp(msg, "cd", 2))    change_directory(msg);
        else {
            bool no_wait = msg[strlen(msg)-1]=='&';
            if(no_wait) {
                msg[strlen(msg)-1] = '\0';
            }
            int new_proc = fork();
            if(new_proc < 0) {
                fprintf(stderr, "%s\n", strerror(errno));
                exit(1);
            } else if(!new_proc) {
                tokenize(msg, envp);
            } else {
                if(no_wait) {
                    num_procs++;
                } else {
                    waitpid(new_proc, NULL, 0);
                }
            }
        }
    }
}
