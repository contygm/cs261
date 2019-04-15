/* CS261- Assignment 1 - Q.3*/
/* Name: 
 * Date: 
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>



char toUpperCase(char ch) {
	/*Convert ch to upper case, assuming it is in lower case currently*/
	return ch - 'a' + 'A';
}

char toLowerCase(char ch) {
	/*Convert ch to lower case, assuming it is in upper case currently*/                          
	return ch - 'A' + 'a';
}

int stringLength(char s[]) {
	/*Return the length of the string*/
	int length = 0;
	while(s[length] != '\0') {
		length++;
	}

	return length;
}


void camelCase(char* word) {
	/*Convert to camelCase*/
	int length = stringLength(word);
	
	// delete non alpha char, convert all to lower case
	for (int i = 0; i < length; i++) {
		// change uppercase to lower case
		if (word[i] >= 65 && word[i] <=90)
		{
			toLowerCase(word[i]);
		} 
		// replace spaces with underscore
		else if (word[i] == 32) {
			word[i] = "_";
		}
		// if not lowercase letter, space or underscore then delete
		else if (word[i] < 97 && word[i] > 122 && word[i] != 32 && word[i] != 95) {
			word[i] = 127;
		}
	}

	// remove duplicate underscores
	for (int i = 0; i < length; i++) {
		if(word[i] == "_" && word[i+1]) {

		}
	}
	
	// camelcase the word
	for (int i = 0; i < length; i++) {
		
	}
}

int main() {

	/*Read the string from the keyboard*/
	char *string = malloc(50 * sizeof(char));
	printf("What string would you like to camelCase? ");

	//TODO: don't allow  "__", "_ _ _", " ", "435%7_$$", "random"
	scanf("%[^\n]s ", string);
	//scanf("%[^\n]%*c", word);
	
	/*Call camelCase*/
	camelCase(string);
	
	/*Print the new string*/
	printf("camelCase string: %s\n", string);

	return 0;
}

