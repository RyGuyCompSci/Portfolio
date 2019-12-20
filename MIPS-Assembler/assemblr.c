/***
 * Assembler for MIPS-32
 * Created for COS 381 - Computer Architecture
 *
 * @author Ryan Jones
 * @version 1.0 2019/09/19
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LENGTH 1024

FILE *fp;
int display_format = 0, debug = 0, geisler = 0;

// helper commands
void print_bits(unsigned bits);
void parse_command(char *str);
void write_to_file(int n);
int translate_register(char *reg);
int masked_value(int shamt, int shval);
void shift_value(int *value, int shamt, int shval);
void get_r_type_values(int *rd, int *rs, int *rt);
void get_i_type_values(int *rs, int *rt, int *immediate);
void r_type_shift(int *instruction, int rs, int rt, int rd);
void i_type_shift(int *instruction, int rs, int rt, int immediate);
void usage();

// conversion of MIPS instructions
void add(int rd, int rs, int rt);
void addi(int rs, int rt, int immediate);
void addu(int rd, int rs, int rt);
void addiu(int rs, int rt, int immediate);
void and(int rd, int rs, int rt);
void andi(int rs, int rt, int immediate);
void beq(int rs, int rt, int immediate);
void bne(int rs, int rt, int immediate);
void j(int address);
void jal(int address);
void jr(int rs);
void lbu(int rs, int rt, int immediate);
void lhu(int rs, int rt, int immediate);
void lui(int rs, int rt, int immediate);
void lw(int rs, int rt, int immediate);
void nor(int rd, int rs, int rt);
void or(int rd, int rs, int rt);
void ori(int rs, int rt, int immediate);
void slt(int rd, int rs, int rt);
void slti(int rs, int rt, int immediate);
void sltiu(int rs, int rt, int immediate);
void sltu(int rd, int rs, int rt);
void sll(int rd, int rt, int shamt);
void srl(int rd, int rt, int shamt);
void sb(int rs, int rt, int immediate);
void sc(int rs, int rt, int immediate);
void sh(int rs, int rt, int immediate);
void sw(int rs, int rt, int immediate);
void sub(int rd, int rs, int rt);
void subu(int rs, int rt, int immediate);
void xor(int rd, int rs, int rt);


//////////////////////////////////////////////////////////////////////
//                      DEFINITION OF HELPERS                       //
//////////////////////////////////////////////////////////////////////


/**
 * Masks bits based on shift amount
 * (makes sure sign-extending doesn't mess with other values)
 */
int masked_value(int shamt, int shval) {
    int mask = 0x01;
	mask <<= shamt;
    mask -= 1;
    return (shval & mask);
}

/**
 * Helper function to add @shamt lsb's as @shval to @value
 */
void shift_value(int *value, int shamt, int shval) {
	*value <<= shamt;
	*value += masked_value(shamt, shval);
}


/**
 * Properly prints all bits for @b
 * Helpful for debugging
 * www.geeksforgeeks.org/binary-representation-of-a-given-number/
 */
void print_bits(unsigned n)
{
    if(debug) {
        if(display_format) {
            printf("0x%08x\n", n);
        } else {
            unsigned i;
            for (i = 1 << 31; i > 0; i = i / 2)
            (n & i)? printf("1"): printf("0");
            printf("\n");
        }
    }
    write_to_file((int) n);
}


void write_to_file(int n) {
    if(fp != NULL) fwrite(&n, 4, 1, fp);
}


/**
 * Gets pointer values for R-type instructions
 */
void get_r_type_values(int *rd, int *rs, int *rt) {
	*rd = translate_register(strtok(NULL, ", "));
	*rs = translate_register(strtok(NULL, ", "));
	*rt = translate_register(strtok(NULL, " \n\r"));
}


/**
 * Gets pointer values for I-type instructions
 */
void get_i_type_values(int *rt, int *rs, int *immediate) {
	*rt = translate_register(strtok(NULL, ", "));
	*rs = translate_register(strtok(NULL, ", "));
    char *imm = strtok(NULL, " \n\r");
    if(strlen(imm) > 1 && !strncmp(imm, "0x", 2)) {
        *immediate = strtol(imm, NULL, 16);
    } else {
        *immediate = atoi(imm);
    }
}


/**
 * Automatically shifts values onto the instruction for an r-type instruction
 */
void r_type_shift(int *instruction, int rs, int rt, int rd) {
	shift_value(instruction, 5, rs);
	shift_value(instruction, 5, rt);
	shift_value(instruction, 5, rd);
	shift_value(instruction, 5, 0x0); // auto-add shift by zero
}


/**
 * Automatically shifts values onto the instruction for an i-type instruction
 */
void i_type_shift(int *instruction, int rs, int rt, int immediate) {
	shift_value(instruction, 5, rs);
	shift_value(instruction, 5, rt);
	shift_value(instruction, 16, immediate);
}


/**
 * Takes a char array and converts it to a register value
 */
int translate_register(char *reg) {
	if(!strcmp(reg, "$zero")) return 0;
	if(!strcmp(reg, "$at"))   return 1;
	if(!strcmp(reg, "$v0"))   return 2;
	if(!strcmp(reg, "$v1"))   return 3;
	if(!strcmp(reg, "$a0"))   return 4;
	if(!strcmp(reg, "$a1"))   return 5;
	if(!strcmp(reg, "$a3"))   return 6;
	if(!strcmp(reg, "$a3"))   return 7;
	if(!strcmp(reg, "$t0"))   return 8;
	if(!strcmp(reg, "$t1"))   return 9;
	if(!strcmp(reg, "$t2"))   return 10;
	if(!strcmp(reg, "$t3"))   return 11;
	if(!strcmp(reg, "$t4"))   return 12;
	if(!strcmp(reg, "$t5"))   return 13;
	if(!strcmp(reg, "$t6"))   return 14;
	if(!strcmp(reg, "$t7"))   return 15;
	if(!strcmp(reg, "$s0"))   return 16;
	if(!strcmp(reg, "$s1"))   return 17;
	if(!strcmp(reg, "$s2"))   return 18;
	if(!strcmp(reg, "$s3"))   return 19;
	if(!strcmp(reg, "$s4"))   return 20;
	if(!strcmp(reg, "$s5"))   return 21;
	if(!strcmp(reg, "$s6"))   return 22;
	if(!strcmp(reg, "$s7"))   return 23;
	if(!strcmp(reg, "$t8"))   return 24;
	if(!strcmp(reg, "$t9"))   return 25;
	if(!strcmp(reg, "$k0"))   return 26;
	if(!strcmp(reg, "$k1"))   return 27;
	if(!strcmp(reg, "$gp"))   return 28;
	if(!strcmp(reg, "$sp"))   return 29;
	if(!strcmp(reg, "$fp"))   return 30;
	if(!strcmp(reg, "$ra"))   return 31;
	else return atoi(reg); // returns numeric value (e.g.: $17)
}


//////////////////////////////////////////////////////////////////////
//                      DEFINITION OF COMMAND                       //
//////////////////////////////////////////////////////////////////////


/**
 * Generates the add command
 */
void add(int rd, int rs, int rt) {
	int instruction = 0;
	// add r-type register values
	r_type_shift(&instruction, rs, rt, rd);
	// add function code
	shift_value(&instruction, 6, 0x20);
	// print results
	print_bits(instruction);
}


/**
 * Generates the addi command
 */
void addi(int rs, int rt, int immediate) {
	int instruction = 0;
	// op code
	shift_value(&instruction, 6, 0x08);
	// add i-type register values
	i_type_shift(&instruction, rs, rt, immediate);
	// print results
	print_bits(instruction);
}


/**
 * Generates the addu command
 */
void addu(int rd, int rs, int rt) {
	int instruction = 0;

	r_type_shift(&instruction, rs, rt, rd);
	shift_value(&instruction, 6, 0x21);

	print_bits(instruction);
}


/**
 * Generates the addiu command
 */
void addiu(int rs, int rt, int immediate) {
	int instruction = 0;

	shift_value(&instruction, 6, 0x09);
	i_type_shift(&instruction, rs, rt, immediate);

	print_bits(instruction);
}


/**
 * Generates the and command
 */
void and(int rd, int rs, int rt) {
	int instruction = 0;

	r_type_shift(&instruction, rs, rt, rd);
	shift_value(&instruction, 6, 0x24);

	print_bits(instruction);
}


/**
 * Generates the andi command
 */
void andi(int rs, int rt, int immediate) {
	int instruction = 0;

	shift_value(&instruction, 6, 0x0c);
	i_type_shift(&instruction, rs, rt, immediate);

	print_bits(instruction);
}


/**
 * Generates the beq command
 */
void beq(int rs, int rt, int immediate) {
	int instruction = 0;

	shift_value(&instruction, 6, 0x04);
	i_type_shift(&instruction, rs, rt, (immediate >> 2));

	print_bits(instruction);
}


/**
 * Generates the bne command
 */
void bne(int rs, int rt, int immediate) {
	int instruction = 0;

	shift_value(&instruction, 6, 0x05);
	i_type_shift(&instruction, rs, rt, (immediate >> 2));

	print_bits(instruction);
}


/**
 * Generates the j command
 */
void j(int address) {
	int instruction = 0;

	shift_value(&instruction, 6, 0x02);
	shift_value(&instruction, 26, (address >> 2));

	print_bits(instruction);
}


/**
 * Generates the jal command
 */
void jal(int address) {
	int instruction = 0;

	shift_value(&instruction, 6, 0x03);
	shift_value(&instruction, 26, (address >> 2));

	print_bits(instruction);
}


/**
 * Generates the jr command
 */
void jr(int rs) {
	int instruction = 0;

	shift_value(&instruction, 5, rs);
	shift_value(&instruction, 15, 0x00);
	shift_value(&instruction, 6, 0x08);

	print_bits(instruction);
}


/**
 * Generates the lbu command
 */
void lbu(int rs, int rt, int immediate) {
	int instruction = 0;

	shift_value(&instruction, 6, 0x24);
	i_type_shift(&instruction, rs, rt, immediate);

	print_bits(instruction);
}



/**
 * Generates the lhu command
 */
void lhu(int rs, int rt, int immediate) {
	int instruction = 0;

	shift_value(&instruction, 6, 0x25);
	i_type_shift(&instruction, rs, rt, immediate);

	print_bits(instruction);
}


/**
 * Generates the ll command
 */
void ll(int rs, int rt, int immediate) {
    int instruction = 0;

    shift_value(&instruction, 6, 0x30);
    i_type_shift(&instruction, rs, rt, immediate);

    print_bits(instruction);
}


/**
 * Generates the lui command
 */
void lui(int rs, int rt, int immediate) {
	int instruction = 0;

	shift_value(&instruction, 6, 0x0f);
	i_type_shift(&instruction, rs, rt, immediate);

	print_bits(instruction);
}


/**
 * Generates the ll command
 */
void lw(int rs, int rt, int immediate) {
    int instruction = 0;

    shift_value(&instruction, 6, 0x23);
    i_type_shift(&instruction, rs, rt, immediate);

    print_bits(instruction);
}


/**
 * Generates the nor command
 */
void nor(int rd, int rs, int rt) {
	int instruction = 0;

	r_type_shift(&instruction, rs, rt, rd);
	shift_value(&instruction, 6, 0x27);

	print_bits(instruction);
}


/**
 * Generates the or command
 */
void or(int rd, int rs, int rt) {
	int instruction = 0;

	r_type_shift(&instruction, rs, rt, rd);
	shift_value(&instruction, 6, 0x25);

	print_bits(instruction);
}


/**
 * Generates the ori command
 */
void ori(int rs, int rt, int immediate) {
	int instruction = 0;

	shift_value(&instruction, 6, 0x0d);
	i_type_shift(&instruction, rs, rt, immediate);

	print_bits(instruction);
}


/**
 * Generates the slt command
 */
void slt(int rd, int rs, int rt) {
	int instruction = 0;

	r_type_shift(&instruction, rs, rt, rd);
	shift_value(&instruction, 6, 0x2a);

	print_bits(instruction);
}


/**
 * Generates the slti command
 */
void slti(int rs, int rt, int immediate) {
	int instruction = 0;

	shift_value(&instruction, 6, 0x0a);
	i_type_shift(&instruction, rs, rt, immediate);

	print_bits(instruction);
}


/**
 * Generates the sltiu command
 */
void sltiu(int rs, int rt, int immediate) {
	int instruction = 0;

	shift_value(&instruction, 6, 0x0b);
	i_type_shift(&instruction, rs, rt, immediate);

	print_bits(instruction);
}


/**
 * Generates the sltu command
 */
void sltu(int rd, int rs, int rt) {
	int instruction = 0;

	r_type_shift(&instruction, rs, rt, rd);
	shift_value(&instruction, 6, 0x2b);

	print_bits(instruction);
}


/**
 * Generates the sll command
 */
void sll(int rd, int rt, int shamt) {
    int instruction = 0;

    shift_value(&instruction, 5, rt);
    if(geisler) shift_value(&instruction, 5, 0x0);
    shift_value(&instruction, 5, rd);
    shift_value(&instruction, 5, shamt);
    shift_value(&instruction, 6, 0x0);

    print_bits(instruction);
}


/**
 * Generates the srl command
 */
void srl(int rd, int rt, int shamt) {
    int instruction = 0;

    shift_value(&instruction, 5, rt);
    if(geisler) shift_value(&instruction, 5, 0x0);
    shift_value(&instruction, 5, rd);
    shift_value(&instruction, 5, shamt);
    shift_value(&instruction, 6, 0x02);

    print_bits(instruction);
}


/**
 * Generates the sb command
 */
void sb(int rs, int rt, int immediate) {
    int instruction = 0;

    shift_value(&instruction, 6, 0x28);
    i_type_shift(&instruction, rs, rt, immediate);

    print_bits(instruction);
}


/**
 * Generates the sc command
 */
void sc(int rs, int rt, int immediate) {
    int instruction = 0;

    shift_value(&instruction, 6, 0x38);
    i_type_shift(&instruction, rs, rt, immediate);

    print_bits(instruction);
}


/**
 * Generates the sh command
 */
void sh(int rs, int rt, int immediate) {
    int instruction = 0;

    shift_value(&instruction, 6, 0x29);
    i_type_shift(&instruction, rs, rt, immediate);

    print_bits(instruction);
}


/**
 * Generates the sw command
 */
void sw(int rs, int rt, int immediate) {
    int instruction = 0;

    shift_value(&instruction, 6, 0x2b);
    i_type_shift(&instruction, rs, rt, immediate);

    print_bits(instruction);
}


/**
 * Generates the sub command
 */
void sub(int rd, int rs, int rt) {
	int instruction = 0;

	r_type_shift(&instruction, rs, rt, rd);
	shift_value(&instruction, 6, 0x22);

	print_bits(instruction);
}


/**
 * Generates the subu command
 */
void subu(int rd, int rs, int rt) {
	int instruction = 0;

	r_type_shift(&instruction, rs, rt, rd);
	shift_value(&instruction, 6, 0x23);

	print_bits(instruction);
}


/**
 * Generates the xor command
 */
void xor(int rd, int rs, int rt) {
    int instruction = 0;

    r_type_shift(&instruction, rs, rt, rd);
    shift_value(&instruction, 6, 0x26);

    print_bits(instruction);
}


//////////////////////////////////////////////////////////////////////
//     					   PARSE OF COMMAND                         //
//////////////////////////////////////////////////////////////////////


/**
 * Determines the command to be run
 */
void parse_command(char *str) {
	char *op = strtok(str, " \n\r");
    if(!op || !strncmp(op, "#", 1)) return; // newline or comment
	// variables to work with
	int address, immediate, rs, rt, rd, shamt;

	if(!strcmp(op, "add")) {
		get_r_type_values(&rd, &rs, &rt);
		add(rd, rs, rt);
	}

	else if(!strcmp(op, "addi")) {
		get_i_type_values(&rt, &rs, &immediate);
		addi(rs, rt, immediate);
	}

	else if(!strcmp(op, "addu")) {
		get_r_type_values(&rd, &rs, &rt);
		addu(rd, rs, rt);
	}

	else if(!strcmp(op, "addiu")) {
		get_i_type_values(&rt, &rs, &immediate);
		addiu(rs, rt, immediate);
	}

	else if(!strcmp(op, "and")) {
		get_r_type_values(&rd, &rs, &rt);
		and(rd, rs, rt);
	}

	else if(!strcmp(op, "andi")) {
		get_i_type_values(&rt, &rs, &immediate);
		andi(rs, rt, immediate);
	}

	else if(!strcmp(op, "beq")) {
		get_i_type_values(&rt, &rs, &immediate);
		beq(rs, rt, immediate);
	}

	else if(!strcmp(op, "bne")) {
		get_i_type_values(&rt, &rs, &immediate);
		bne(rs, rt, immediate);
	}

    else if(!strcmp(op, "halt")) {
        print_bits(0xffffffff);
    }

	else if(!strcmp(op, "j")) {
        char *addr = strtok(NULL, "\n\r");
        if(!strncmp(addr, "0x", 2)) {
            address = strtol(addr, NULL, 16);
        } else {
    		address = atoi(addr);
        }
		j(address);
	}

	else if(!strcmp(op, "jal")) {
        char *addr = strtok(NULL, "\n\r");
        if(!strncmp(addr, "0x", 2)) {
            address = strtol(addr, NULL, 16);
        } else {
    		address = atoi(addr);
        }
		jal(address);
	}

	else if(!strcmp(op, "jr")) {
		rs = translate_register(strtok(NULL, "\n\r"));
		jr(rs);
	}

	else if(!strcmp(op, "lbu")) {
		get_i_type_values(&rt, &rs, &immediate);
		lbu(rs, rt, immediate);
	}

	else if(!strcmp(op, "lhu")) {
		get_i_type_values(&rt, &rs, &immediate);
		lhu(rs, rt, immediate);
	}

    else if(!strcmp(op, "ll")) {
        get_i_type_values(&rt, &rs, &immediate);
        ll(rs, rt, immediate);
    }

	else if(!strcmp(op, "lui")) {
		get_i_type_values(&rt, &rs, &immediate);
		lui(rs, rt, immediate);
	}

	else if(!strcmp(op, "lw")) {
		rt = translate_register(strtok(NULL, ", "));
        char *imm = strtok(NULL, "(");
        if(strlen(imm) > 2 && !strncmp(imm, "0x", 2)) {
            immediate = (int)strtol(imm, NULL, 0);
        } else {
    		immediate = atoi(imm);
        }
		rs = translate_register(strtok(NULL, ")"));
		lw(rs, rt, immediate);
	}

	else if(!strcmp(op, "nop")) {
		print_bits(0x0);
	}

	else if(!strcmp(op, "nor")) {
		get_r_type_values(&rd, &rs, &rt);
		nor(rd, rs, rt);
	}

	else if(!strcmp(op, "or")) {
		get_r_type_values(&rd, &rs, &rt);
		or(rd, rs, rt);
	}

	else if(!strcmp(op, "ori")) {
		get_i_type_values(&rt, &rs, &immediate);
		ori(rs, rt, immediate);
	}

	else if(!strcmp(op, "slt")) {
		get_r_type_values(&rd, &rs, &rt);
		slt(rd, rs, rt);
	}

	else if(!strcmp(op, "slti")) {
		get_i_type_values(&rt, &rs, &immediate);
		slti(rs, rt, immediate);
	}

	else if(!strcmp(op, "sltiu")) {
		get_i_type_values(&rt, &rs, &immediate);
		sltiu(rs, rt, immediate);
	}

	else if(!strcmp(op, "sltu")) {
		get_r_type_values(&rd, &rs, &rt);
		sltu(rd, rs, rt);
	}

	else if(!strcmp(op, "sll")) {
        get_r_type_values(&rd, &rs, &shamt);
        sll(rd, rs, shamt);
	}

	else if(!strcmp(op, "srl")) {
        get_r_type_values(&rd, &rs, &shamt);
        srl(rd, rs, shamt);
	}

    else if(!strcmp(op, "sb")) {
		rt = translate_register(strtok(NULL, ", "));
		immediate = atoi(strtok(NULL, "("));
		rs = translate_register(strtok(NULL, ")"));
		sb(rs, rt, immediate);
    }

    else if(!strcmp(op, "sc")) {
		rt = translate_register(strtok(NULL, ", "));
		immediate = atoi(strtok(NULL, "("));
		rs = translate_register(strtok(NULL, ")"));
		sc(rs, rt, immediate);
    }

    else if(!strcmp(op, "sh")) {
		rt = translate_register(strtok(NULL, ", "));
		immediate = atoi(strtok(NULL, "("));
		rs = translate_register(strtok(NULL, ")"));
		sh(rs, rt, immediate);
    }

    else if(!strcmp(op, "sw")) {
		rt = translate_register(strtok(NULL, ", "));
        char *imm = strtok(NULL, "(");
        if(strlen(imm) > 1 && !strncmp(imm, "0x", 2)) {
            immediate = (int)strtol(imm, NULL, 0);
        } else {
    		immediate = atoi(imm);
        }
		rs = translate_register(strtok(NULL, ")"));
		sw(rs, rt, immediate);
    }

    else if(!strcmp(op, "sub")) {
        get_r_type_values(&rd, &rs, &rt);
        sub(rd, rs, rt);
    }

    else if(!strcmp(op, "subu")) {
        get_r_type_values(&rd, &rs, &rt);
        subu(rd, rs, rt);
    }

    else if(!strcmp(op, "xor")) {
        get_r_type_values(&rd, &rs, &rt);
        xor(rd, rs, rt);
    }

	else { // handles unknown commands
		printf("Unknown command: %s\n", op);
        usage();
	}
}


void usage() {
    printf("\n-d : show debug output\n");
    printf("-b : show output as bits [default]\n");
    printf("-h : show output as hex\n");
    printf("-o : write values to 0x1000\n");
    printf("-g : accounts for Geisler's implementation\n\n");
}


/**
 * Main function of the program
 */
int main(int argc, char **argv, char **envp) {

    int c;
    int start_at_thousand = 0;
    while((c = getopt(argc, argv, "bdhog")) != -1) {
        switch(c) {
            case 'b':
                display_format = 0;
                break;
            case 'd':
                debug = 1;
                break;
            case 'h':
                display_format = 1;
                break;
            case 'o':
                start_at_thousand = 1;
                break;
            case 'g':
                geisler = 1;
                break;
            defualt:
                break;
        }
    }

    fp = fopen("data.bin", "w");

    if(start_at_thousand) {
        int n = 0;
        for(int i = 0; i < 0x1000; i+=4) {
            fwrite(&n, 4, 1, fp);
            n++;
        }
    }

	char input[MAX_LENGTH];
	while(fgets(input, MAX_LENGTH, stdin) != NULL) {
		parse_command(input);
	}

	return 0;
}
