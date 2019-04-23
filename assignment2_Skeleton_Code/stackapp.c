/*	bracketsStack.c: bracketsStack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using bracketsStack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
			
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: 	
	post:	
*/
int isBalanced(char* s)
{
	/* FIXME: You will write this function */	
	DynArr * bracketsStack;
	bracketsStack = newDynArr(1);

	char x;

	do {
		x = nextChar(s);

		switch(x) {
			// if opening bracket, push into stack
			case '(':
			case '{':
			case '[':
				pushDynArr(bracketsStack, x);
				break;

			// if closing bracket, check for match
			case ')':
			case '}':
			case ']':
				// make sure array isn't empty, before checking for top
				if (sizeDynArr(bracketsStack) == 0) {
					deleteDynArr(bracketsStack);
					return 0;
				} else if ((topDynArr(bracketsStack) == '(' && x == ')') 
					|| (topDynArr(bracketsStack) == '[' && x == ']')
					|| (topDynArr(bracketsStack) == '{' && x == '}')
					) {
					// check if top matches closing bracket type
					// remove from back if yes
					popDynArr(bracketsStack);
				} else {
					// push into array if doesn't match top bracket type
					pushDynArr(bracketsStack, x);
				}
				break;
		}

	} while (x != '\0');

	// if stack is emptey after do/while, it is balanced
	if (sizeDynArr(bracketsStack) == 0)
	{
		deleteDynArr(bracketsStack);
		return 1;
	}

	// if stack isn't empty, not balanced
	deleteDynArr(bracketsStack);	
	return 0;
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}