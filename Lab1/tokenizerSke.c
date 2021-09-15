#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXLINE 100
/* Return true (non-zero) if c is a whitespace characer
   ('\t' or ' ').
   Zero terminators are not printable (therefore false) */
bool delim_character(char c){
	if(c==' '||c=='\t')
		return 1;
	return 0;
}

/* Return true (non-zero) if c is a non-whitespace
   character (not tab or space).
   Zero terminators are not printable (therefore false) */
bool non_delim_character(char c){
	if(c=='\0'|| c==' ' || c=='\t')
		return 0;
	return 1;
}

/* Returns a pointer to the first character of the next
   space-separated word*/
char *word_start(char* str){
	

}

/* Returns a pointer to the first space character of the zero
terminated string*/
char *end_word(char* str){

}
// counts the number of words or tokens
int count_tokens(char* str){


}
/* Returns a freshly allocated zero-terminated vector of freshly allocated
   space-separated tokens from zero-terminated str.
   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string"
     tokens[3] = 0
*/
char *copy_str(char *inStr, short len){

}

char** tokenize(char* str){
	printf("I'm in the tokenize function.\n");
	printf("The string is: %s\n", &str);
	//Start breaking into tokens
	
	return;

}


void print_all_tokens(char** tokens){
}

int main(){
	int c, i;
	char *strtoken;
	//Get string to tokenize
	printf("Enter your string to tokenize. LIMIT 100 CHARACTERS.\n");
	printf("$");
	/*for(i=0; i<MAXLINE-1 && (c=getchar())!=EOF && c!='\n'; i++){
		strtoken[i] = c;
	}*/
	fgets(strtoken, MAXLINE, stdin);
	
	printf("The string is: %s\n", strtoken);
	printf("This is the address of my string: %d\n", &strtoken);
	printf("This is the address of the first character of the string: %d\n", &strtoken[0]);
	printf("This is the address of the second character of the string: %d\n", &strtoken[1]);
	
	for(char character = *strtoken; character!='\0'; character=*++strtoken){
		printf("%c\n",character);
	}
	
	tokenize(strtoken);
	
	return 0;
}

