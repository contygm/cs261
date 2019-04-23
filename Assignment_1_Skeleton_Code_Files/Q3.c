/* CS261- Assignment 1 - Q.3*/
/* Name: Genevieve Conty
 * Date: 04/15/2019
 * Solution description: HW Solution - Q.3
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
	int originalLength = stringLength(word);

	
	// delete non alpha char, convert all to lower case
	for (int i = 0; i < length; i++) {
		// change uppercase to lower case
		if (word[i] >= 65 && word[i] <=90)
		{
			word[i] = toLowerCase(word[i]);
		} 
		// replace spaces with underscore
		else if (word[i] == 32) {
			word[i] = 95;
		}
		// if not lowercase letter, space or underscore then delete
		else if ((word[i] < 97 || word[i] > 122) && word[i] != 32 && word[i] != 95) {
			word[i] = 95;
		}
	}

	// remove duplicate underscores
	for (int i = 0; i < length; i++) {
		if(word[i] == "_" && word[i+1] == "_") {
			while (word[i] != '\0' && word[i+1] != '\0') {
				word[i] = word[i+1];
			}
		}
	}

	// camelcase the word
	for (int i = 0; i < length; i++) {
		if(word[i] == 95) {
			for (int j = i; j < length; j++) {
				word[j] = word[j+1];
			}
			length--;
			word[i] = toUpperCase(word[i]);
		}
	}

	/*Print the new string*/
	if (length <= 0 || originalLength == length) {
		printf("invalid input string \n");
	} else {
		for (int i = 0; i < length; i++)
		{
			printf("%c", word[i]);
		}

		printf("\n");
	}
}

int main() {

	/*Read the string from the keyboard*/
	char *string = malloc(50 * sizeof(char));
	printf("What string would you like to camelCase? ");

	scanf("%[^\n]s ", string);
	
	/*Call camelCase*/
	camelCase(string);
	
	return 0;
}

