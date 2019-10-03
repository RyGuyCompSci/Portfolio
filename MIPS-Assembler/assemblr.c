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

#define MAX_LENGTH 1024

// helper commands
void print_bits(unsigned bits);
void parse_command(char *str);
int translate_register(char *reg);
int masked_value(int shamt, int shval);
void shift_value(int *value, int shamt, int shval);
void get_r_type_values(int *rd, int *rs, int *rt);
void get_i_type_values(int *rs, int *rt, int *immediate); 
void r_type_shift(int *instruction, int rs, int rt, int rd);
void i_type_shift(int *instruction, int rs, int rt, int immediate);

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
void nop ();


//////////////////////////////////////////////////////////////////////
//                      DEFINITION OF HELPERS                       //
//////////////////////////////////////////////////////////////////////


/**
 * Masks bits based on shift amount
 * (makes sure sign-extending doesn't mess with other values)
 */
int masked_value(int shamt, int shval) {
    int mask = 0x01;
    for(int i = 0; i < shamt; i++) {
        mask <<= 2;
    }
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
    unsigned i; 
    for (i = 1 << 31; i > 0; i = i / 2) 
        (n & i)? printf("1"): printf("0"); 
    printf("\n");
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
	*immediate = atoi(strtok(NULL, " \n\r"));
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
	//else return atoi(reg + 1); // returns numeric value (e.g.: $17)
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
	i_type_shift(&instruction, rs, rt, immediate);

	print_bits(instruction);
}


/**
 * Generates the bne command
 */
void bne(int rs, int rt, int immediate) {
	int instruction = 0;

	shift_value(&instruction, 6, 0x05);
	i_type_shift(&instruction, rs, rt, immediate);

	print_bits(instruction);
}


/**
 * Generates the j command
 */
void j(int address) {
	int instruction = 0;
	
	shift_value(&instruction, 6, 0x02);
	shift_value(&instruction, 26, address);

	print_bits(instruction);
}


/**
 * Generates the jal command
 */
void jal(int address) {
	int instruction = 0;

	shift_value(&instruction, 6, 0x03);
	shift_value(&instruction, 26, address);

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
 * Prints all bit-zeroes
 */
void nop() {
    printf("%032d\n", 0);
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


//////////////////////////////////////////////////////////////////////
//     					   PARSE OF COMMAND                         //
//////////////////////////////////////////////////////////////////////


/**
 * Determines the command to be run
 */
void parse_command(char *str) {
	char *op = strtok(str, " \n\r");

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
	
	else if(!strcmp(op, "j")) {
		address = atoi(strtok(NULL, "\n\r"));
		j(address);
	}
	
	else if(!strcmp(op, "jal")) {
		address = atoi(strtok(NULL, "\n\r"));
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
		immediate = atoi(strtok(NULL, "("));
		rs = translate_register(strtok(NULL, ")"));
		lw(rs, rt, immediate);
	}
	
	else if(!strcmp(op, "nop")) {
		nop();
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

	else if(!strcmp(op, "sll")) {
		
	}
	
	else { // handles unknown commands
		printf("Unknown command: %s\n", op);
	}
}


/**
 * Main function of the program
 */
int main(int argc, char **argv, char **envp) {

	char input[MAX_LENGTH];
	while(fgets(input, MAX_LENGTH, stdin) != NULL) {
		parse_command(input);
	}

	return 0;
}
