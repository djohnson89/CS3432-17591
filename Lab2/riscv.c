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
	return true;
}

/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */
bool interpret(char* instr){
	//Get first token
	char* token = strtok(instr, " ");
	//Loop through tokens
	while(token!=NULL){
		//Instructions: Load (LW), Add (ADD), Add Immediate (ADDI), Store (SW)
		if(string_compare(token, "LW")){
			printf("First token is LW for load word.\n");
			printf("Reading address: %x\n", read_address(0x5, "mem.txt"));
		}
		else if(string_compare(token, "ADD")){
			printf("First token is ADD for addition\n");
		}
		else if(string_compare(token, "ADDI")){
			printf("First token is ADDI for add immediate\n");
		}
		else if(string_compare(token, "SW")){
			printf("First token is SW for store word.\n");
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
	int c;
	printf("\nEnter your RISC-V Instructions.\nEnter instructions in ALL CAPITAL LETTERS.\nUse spaces between parameters.\nSubmit an EOF character to exit.\n$");
	fgets(instructions, 50, stdin);
	printf("Your instruction: %s\n", instructions);
	interpret(instructions);

	return 0;
}
