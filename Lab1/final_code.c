#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXLINE 20

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
	//Allocate memory for new token
	token = (char *) malloc(len*sizeof(char));
	//Add characters from tokenized string individually.
	while(i<len){
		token[i] = *inStr;
		i++;
		inStr++;
	}
	token[i+1]='\0';
	return token;
		
}

char** tokenize(char* str){
	char *temp = str, *start = str;
	int c, i, j, tokens;
	
	//Count the number of tokens in the string.
	tokens = count_tokens(temp);
	
	//Create array 
	char **token_store[tokens][0];
	
	//Assign the current character of temp to c for looping.
	c=*temp;
	//Set the start as the beginning of the string.
	start = str;
	//Loop while c is not a newline or null terminator character
	while(c!='\n' && c!='\0'){
		//Increment through temp until a space is found
		//or a newline or null terminator character is found.
		for(i=0; *temp!=' ' && (*temp!='\n' && *temp!='\0'); i++){
			temp++;
		}
		//Assign first line of the token store array to the returned address of copy_str.
		token_store[j][0] = (copy_str(start, i));
		printf("Token[%d]: %s\n", j, *(&token_store[j][0]));
		//Increment the variables to the current values.
		temp++;
		c=*temp;
		j++;
		//Set start as the new location of temp which sould be the beginning of the next token.
		start = temp;
		
		
	}
	return token_store;
}

int main(){
	char mystring[MAXLINE];
	char *strptr;
	
	printf("Enter a string. Limit 20 characters.\n$");
	fgets(mystring, MAXLINE, stdin);
	
	strptr = mystring;
	printf("Your string: %s\n", mystring);
	tokenize(strptr);
	
	return 0;
	
}
