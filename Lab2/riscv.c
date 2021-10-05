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
	if(*tok==*instr) return true;
	else return false;
}

int strtoint(char* s){
	int i, n;
	n = 0;
	//Move past X character in the token
	if(*s=='X') s++;
	for(;*s>='0' && *s<='9'; s++){
		n = 10 * n + (*s - '0');
	}
	//Return register multiplied by 4 for byte compensation
	return n;
}
void load_word(char* dest, char* src){
	
}

void store_word(){

}

void add(int dest, int src_1, int src_2){
	int32_t line_address = dest * 4;
	int data = reg[src_1] + reg[src_2];
	reg[dest] = data;
	write_address(reg[dest], line_address, "mem.txt");
}

void addi(int dest, int src, int n){
	int32_t line_address = dest * 4;
	printf("reg[src] is: %d\n", reg[src]);
	n = reg[src] + n;
	printf("N is: %d, reg[src] is: %d\n", n, reg[src]);
	reg[dest] = n;
	write_address(reg[dest], line_address, "mem.txt");
}
void print_reg(){
	int column = 10;
	for(int i=0; i<8; i++){
		printf("X%02i:%.*lld\t", i ,column, (long long int) reg[i]);
		printf("X%02i:%.*lld\t", i+8, column, (long long int) reg[i+8]);
		printf("X%02i:%.*lld\t", i+16, column, (long long int) reg[i+16]);
		printf("X%02i:%.*lld\n", i+24, column, (long long int) reg[i+24]);
	}
	printf("\n");
}

/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */
bool interpret(char* instr){
	printf("Instruction: %s\n", instr);
	//Get first token
	char* token = strtok(instr, " ");
	//variables for registers and data
	int32_t reg_1, reg_2, reg_3, data;
	//Loop through tokens
	while(token!=NULL){
		//Instructions: Load (LW), Add (ADD), Add Immediate (ADDI), Store (SW)
		if(string_compare(token, "LW")){
			token=strtok(NULL, " ");
			reg_1 = strtoint(token);
			printf("reg_1: %d\n", reg_1);
			token=strtok(NULL, " ");
			reg_2 = strtoint(token);
			printf("reg_2: %d\n", reg_2);
			data = read_address(reg_2, "mem.txt");
			write_address(data, reg_1, "mem.txt");
			return true;
		}
		else if(string_compare(token, "ADD")){
			printf("First token is ADD for addition\n");
			reg_1=strtoint(strtok(NULL, " "));
			reg_2=strtoint(strtok(NULL, " "));
			reg_3=strtoint(strtok(NULL, " "));
			add(reg_1, reg_2, reg_3);
			return true;
			
		}
		else if(string_compare(token, "ADDI")){
			reg_1 = strtoint(strtok(NULL, " "));
			reg_2 = strtoint(strtok(NULL, " "));
			data = strtoint(strtok(NULL, " "));
			/*data = read_address(reg_2, "mem.txt");
			data = data + reg_3;
			write_address(data, reg_1, "mem.txt");
			*/
			printf("reg_1 is: %d, reg_2 is: %d\n", reg_1, reg_2);
			addi(reg_1, reg_2, data);
			return true;
		}
		else if(string_compare(token, "SW")){
			printf("First token is SW for store word.\n");

		}
		else{
			//Instructions do not match, return false.
			printf("Invalid instruction.\n");
			return false;
		}
	}
	//Print line of mem.txt
	print_reg();
	return true;
}


/**
 * Simple demo program to show the usage of read_address() and write_address() found in memory.c
 * Before and after running this program, look at mem.txt to see how the values change.
 * Feel free to change "data_to_write" and "address" variables to see how these affect mem.txt
 * Use 0x before an int in C to hardcode it as text, but you may enter base 10 as you see fit.
 */
void write_read_demo(){
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

/**
 * Your code goes in the main
 *
 */

int main(){
	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE

	// Below is a sample program to a write-read. Overwrite this with your own code.
	write_read_demo();
	
	char instructions[50];
	bool finished = false;
	printf("\nEnter your RISC-V Instructions.\nEnter instructions in ALL CAPITAL LETTERS.\nUse spaces between parameters.\nSubmit an EOF character to exit.\n$");
	do{
	fgets(instructions, 50, stdin);
	interpret(instructions);
	print_reg();
	}while(!finished);

	return 0;
}
