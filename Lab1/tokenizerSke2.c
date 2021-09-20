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
	char *curr;
	while(*curr!=' '){
		curr++;
	}
	curr++;
	start = curr;
	return start;
}

/* Returns a pointer to the first space character of the zero
terminated string*/
char *end_word(char* str){
	char *end;
	char *curr;
	while(*curr!=' '){
		curr++;
	}
	curr++;
	end = curr;
	return end;

}
// counts the number of words or tokens
int count_tokens(char* str){
	//Tokens = whitespace(n) + 1.
	//i.e. "This is my string." 3 spaces, 4 words
	int count = 0;
	char *curr;
	curr = str;

	while(*curr!='\n' && *curr!='\0'){
		if(*curr==' ')
			count++;
		curr++;
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
	//printf("\nLen: %d\n", len);
	token = (char *) malloc(len*sizeof(char));
	while(i<len){
		//printf("Copying character: %c\n", *inStr);
		token[i] = *inStr;
		//printf("copy_str token: %s\n", token);
		i++;
		inStr++;
	}
	token[i+1]='\0';
	//printf("copy token: %s\n", token);
	return token;
		
}

char** tokenize(char* str){
	char *temp = str;
	char *copy, *start;
	int c, i, j, tokens;
	tokens = count_tokens(temp);
	char **token_store[tokens][0];
	/*
	Use a while loop using the token count.
	while(i=0; i<tokens; i++)
	*/
	printf("Tokens: %d\n", tokens);
	c=*temp;
	start = str;
	while(c!='\n' && c!='\0'){
		for(i=0; *temp!=' ' && (*temp!='\n' && *temp!='\0'); i++, temp++){
		}
		//printf("\ni is: %d\n", i);
		copy = copy_str(start, i);
		//printf("Copied token = %s\n", copy);
		token_store[j][0] = copy;
		printf("Token[%d]: %s\n", j, *(&token_store[j][0]));
		temp++;
		c=*temp;
		start = temp;
		j++;
		
	}
	//for(i=0; i<tokens; i++)
	//	printf("Token[%d]: %s\n", i, *(&token_store[i][0]));
	return token_store;
}


void print_all_tokens(char** tokens){

}
int main(){
	char mystring[MAXLINE];
	char *strptr;
	
	printf("Enter a string. Limit 20 characters.\n$");
	fgets(mystring, MAXLINE, stdin);
	
	strptr = mystring;
	printf("String: %s\n", mystring);
	tokenize(strptr);
	
	return 0;
	
}
