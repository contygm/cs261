#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// CITATION: https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
    // REVIEW: implement
    char * word = nextWord(file);
    while (word)
    {
        hashMapPut(map, word, 1);
        free(word);
        word = nextWord(file);
    }

    free(word); 
}


/**
 * CITATION: https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C
 * Performs levenshtein algorithm, not recursive version
 * @param t
 * @param s
 */
int levenshtein(char *s1, char *s2) {
    unsigned int s1len, s2len, x, y, lastdiag, olddiag;
    s1len = strlen(s1);
    s2len = strlen(s2);
    unsigned int column[s1len+1];
    for (y = 1; y <= s1len; y++)
        column[y] = y;
    for (x = 1; x <= s2len; x++) {
        column[0] = x;
        for (y = 1, lastdiag = x-1; y <= s1len; y++) {
            olddiag = column[y];
            column[y] = MIN3(column[y] + 1, column[y-1] + 1, lastdiag + (s1[y-1] == s2[x-1] ? 0 : 1));
            lastdiag = olddiag;
        }
    }
    return(column[s1len]);
}
 

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    
    HashMap* map = hashMapNew(1000);
    
    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
    
    char inputBuffer[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);
        
        // REVIEW: implement
        // Implement the spell checker code here..

        // go to lowercase for case insensitive
        for (int j = 0; j < strlen(inputBuffer); j++)
        {
            inputBuffer[j] = tolower(inputBuffer[j]);   
        }

        // if word is 'Quit' program quits
        if (strcmp(inputBuffer, "Quit") == 0) {
            quit = 1;
        } else if (hashMapContainsKey(map, inputBuffer)) { // check if word is in dictionary
            printf("The inputted word %s is spelled correctly. \n", inputBuffer);
        } else { // NOT spelled correctly
            printf("The inputted word %s is spelled incorrectly. \n Did you mean...?", inputBuffer);
            
            // suggest 5 possible words
            HashMap * suggested = hashMapNew(5);

            // go thru dictionary
            for (int i = 0; i < map->capacity; i++)
            {
                HashLink * current = map->table[i];
                int levFactor = levenshtein(inputBuffer, current->key);
                int count = 0;

                // if count less than 5, just insert word at next space
                if(count < 5) {
                    hashMapPut(suggested, current->key, levFactor);
                    count++;
                } else {
                    // compare current with all suggested words
                    for (int n = 0; n < 5; n++)
                    {
                        // replace if levFactor is lower
                        if(levFactor < suggested->table[n]->value) {
                            // remove
                            hashMapRemove(suggested, suggested->table[n]->key);
                            // put
                            hashMapPut(suggested, current->key, levFactor);
                        }
                    }
                }
            }
            // print suggested
            hashMapPrint(suggested);
        }
    }
    
    hashMapDelete(map);
    return 0;
}

