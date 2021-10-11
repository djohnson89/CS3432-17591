#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // malloc & free
#include <stdint.h> // use guaranteed 64-bit integers
// #include "tokenizer.h" // Create header file and reference that
#include "memory.h" // built-in functions to read and write to a specific file
#include <strings.h> //For fgets and strtok functions
#include <string.h> //For strtok

int32_t* reg; // Array of 32 32-bit registers

void init_regs();
bool interpret(char* instr);
void write_read_demo();

/**
 * Initialize register array for usage.
 * Malloc space for each 32-bit register then initializes each register to 0.
 * Do not alter this function!
 */
void init_regs(){
	int reg_amount = 32;
	reg = malloc(reg_amount * sizeof(int32_t)); // 32 * 4 bytes
	for(int i = 0; i < 32; i++)
		reg[i] = i;
}
//Stirng_Compare to find which instruction to execute
bool string_compare(char* tok, char* instr){
	while(*tok!='\0' && *instr!='\0'){
		//Current characters match, move to next character in string
		if(*tok == *instr){
			tok++;
			instr++;
		}
		else if(*tok!=*instr){
			return false;
		}
		//Strings are not equal, return false
		else if(*tok == '\0' && *instr!='\0'){
			return false;
		}
		else if(*tok!='\0' && *instr=='\0'){
			return false;
		}
	}
	//Final Check for instructions matching
	//Case for differentiating between ADD and ADDI
	if(*tok==*instr) return true;
	else return false;
}

int strtoint(char* s){
	int n;
	bool is_negative = false;
	n = 0;
	//Move past X character in the token
	if(*s=='X') s++;
	//Check for negative number
	if (*s=='-'){
		is_negative = true;
		s++;
	}
	for(;*s>='0' && *s<='9'; s++){
		n = 10 * n + (*s - '0');
	}
	//Return positive or negative depending on if '-' was present
	if(is_negative) return n*-1;
	return n;
}

void load_word(int rd, int offset, int rs1){
	//Address in memory.c is address / 2
	int32_t address = offset * 2;
	int32_t data = read_address(address, "mem.txt");
	reg[rd] = data;
	
}
//SW X1 5(X2) - X1 has the value being stored and 5 is the line in mem.txt to write to.
void store_word(int rd, int offset, int rs1){
	//Address in memory.c is address / 2
	int32_t address = offset * 2;
	int32_t data = reg[rd];
	write_address(data, address, "mem.txt");
}

void add(int rd, int rs1, int rs2){
	reg[rd] = reg[rs1] + reg[rs2];
}

void addi(int rd, int rs1, int n){
	n = reg[rs1] + n;
	reg[rd] = n;
}

void and(int rd, int rs1, int rs2){
	reg[rd] = rs1 & rs2;
}

void or(int rd, int rs1, int rs2){
	reg[rd] = rs1 | rs2;
}

void xor(int rd, int rs1, int rs2){
	reg[rd] = rs1 ^ rs2;
}
void print_reg(){
	int column = 10;
	for(int i=0; i<8; i++){
		printf("X%02i:%.*lld\t", i ,column, (long long int) reg[i]);
		printf("X%02i:%.*lld\t", i+8, column, (long long int) reg[i+8]);
		printf("X%02i:%.*lld\t", i+16, column, (long long int) reg[i+16]);
		printf("X%02i:%.*lld\n", i+24, column, (long long int) reg[i+24]);
	}
}

/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */
bool interpret(char* instr){
	//Get first token
	char* token = strtok(instr, " ");
	//variables for registers and data
	int32_t reg_1, reg_2, reg_3; //Registers
	int32_t imm, offset; //imm for ADDI, offset for LW and SW
	//Loop through tokens
	while(token!=NULL){
		//Instructions: Load (LW), Add (ADD), Add Immediate (ADDI), Store (SW)
		//Assuming convention of LW Xn1 offset(Xn2)
		if(string_compare(token, "LW")){ //Load Word
			reg_1 = strtoint(strtok(NULL, " ")); // Destination Register
			offset = strtoint(strtok(NULL, "(")); // Offset
			reg_2 = strtoint(strtok(NULL, ")")); //Source register
			load_word(reg_1, offset, reg_2);
			return true;
		}
		else if(string_compare(token, "ADD")){ //Add
			reg_1=strtoint(strtok(NULL, " "));
			reg_2=strtoint(strtok(NULL, " "));
			reg_3=strtoint(strtok(NULL, " "));
			add(reg_1, reg_2, reg_3);
			return true;
			
		}
		else if(string_compare(token, "ADDI")){ //Add immediate
			reg_1 = strtoint(strtok(NULL, " "));
			reg_2 = strtoint(strtok(NULL, " "));
			imm = strtoint(strtok(NULL, " "));
			addi(reg_1, reg_2, imm);
			return true;
		}
		//Assuming convention of LW Xn1 offset(Xn2)
		else if(string_compare(token, "SW")){ // Store word
			reg_1 = strtoint(strtok(NULL, " "));
			offset = strtoint(strtok(NULL, "(")); // Offset
			reg_2 = strtoint(strtok(NULL, ")")); 
			store_word(reg_1, offset, reg_2);
			return true;

		}
		//Extra Credit Functions, AND OR XOR
		else if(string_compare(token, "AND")){
			reg_1 = strtoint(strtok(NULL, " "));
			reg_2 = strtoint(strtok(NULL, " "));
			reg_3 = strtoint(strtok(NULL, " "));
			and(reg_1, reg_2, reg_3);
			return true;	
		}
		else if(string_compare(token, "OR")){
			reg_1 = strtoint(strtok(NULL, " "));
			reg_2 = strtoint(strtok(NULL, " "));
			reg_3 = strtoint(strtok(NULL, " "));
			or(reg_1, reg_2, reg_3);
			return true;
		}
		else if(string_compare(token, "XOR")){
			reg_1 = strtoint(strtok(NULL, " "));
			reg_2 = strtoint(strtok(NULL, " "));
			reg_3 = strtoint(strtok(NULL, " "));
			xor(reg_1, reg_2, reg_3);
			return true;
		}
		else{
			//Instructions do not match, return false.
			printf("Invalid instruction.\n");
			return false;
		}
		token=strtok(NULL, " ");
	}
	return true;
}


/**
 * Simple demo program to show the usage of read_address() and write_address() found in memory.c
 * Before and after running this program, look at mem.txt to see how the values change.
 * Feel free to change "data_to_write" and "address" variables to see how these affect mem.txt
 * Use 0x before an int in C to hardcode it as text, but you may enter base 10 as you see fit.
 */
/*void write_read_demo(){
	int32_t data_to_write = 0xFFF; // equal to 4095
	int32_t address = 0x98; // equal to 152
	char* mem_file = "mem.txt";

	// Write 4095 (or "0000000 00000FFF") in the 20th address (address 152 == 0x98)
	int32_t write = write_address(data_to_write, address, mem_file);
	if(write == (int32_t) NULL)
		printf("ERROR: Unsucessful write to address %0X\n", 0x40);
	int32_t read = read_address(address, mem_file);

	printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned
}
*/
/**
 * Your code goes in the main
 *
 */

int main(){
	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE

	// Below is a sample program to a write-read. Overwrite this with your own code.
	//write_read_demo();
	
	char* instruction = malloc(1000 * sizeof(char));
	bool is_null = false;
	printf(" RV32 Interpreter.\nType RV32 instructions. Use upper-case letters and space as a delimiter.\nEnter 'EOF' character to end program\n");
	is_null = fgets(instruction, 1000, stdin) == NULL;
	while(!is_null){
		interpret(instruction);
		printf("\n");
		print_reg();
		printf("\n");
		is_null = fgets(instruction, 1000, stdin) == NULL;
	}


	return 0;
}
