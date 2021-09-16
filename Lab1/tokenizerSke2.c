#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXLINE 20
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
	char *start;
	while(*str!=' '){
		str++;
	}
	str++;
	start = str;
	return start;
}

/* Returns a pointer to the first space character of the zero
terminated string*/
char *end_word(char* str){
	char *end;
	while(*str!=' '){
		str++;
	}
	str++;
	end = str;
	return end;

}
// counts the number of words or tokens
int count_tokens(char* str){
	//Tokens = whitespace(n) + 1.
	//i.e. "This is my string." 3 spaces, 4 words
	int count = 0;
	while(*str!='\n' && *str!='\0'){
		if(*str==' ')
			count++;
		str++;
	}
	return count+1;

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
	char *token;
	int i=0;
	token = (char *) malloc(len*sizeof(char));
	while(i<len){
		token[i] = *inStr;
		i++;
		inStr++;
	}
	
	return token;
		
}

char** tokenize(char* str){
	char *temp = str;
	char *copy, *start;
	int c, i, j, tokens;
	tokens = count_tokens(temp);
	char** token_store[tokens][0];
	
	printf("Tokens: %d\n", tokens);
	c=*temp;
	while(c!='\n' && c!='\0'){
		for(i=0; *temp!=' ' && (*temp!='\n' && *temp!='\0'); i++, temp++){
			printf("Looping because Temp = %c\n", *temp);
		}
		printf("i is: %d\n", i);
		copy = copy_str(start, i);
		printf("Copied token = %c\n", *copy);
		token_store[j][0] = copy;
		temp++;
		c=*temp;
		start = temp;
		j++;
		
		
	}
	print_all_tokens(token_store);
	/*while(c!='\n'){
		for(; *temp!=' '; temp++){
			c = *temp;
			printf("C is: %c\n", c);
			if(delim_character(*temp)==1){
				printf("Delim found!");
			}
		}
		temp++;
		c = *temp;		
	}*/
}


void print_all_tokens(char** tokens){

}
int main(){
	char mystring[MAXLINE];
	char *strptr;
	
	printf("Enter a string. Limit 20 characters.\n$");
	fgets(mystring, MAXLINE, stdin);
	
	strptr = &mystring;
	printf("String: %s\n", mystring);
	tokenize(strptr);
	
	return 0;
	
}
