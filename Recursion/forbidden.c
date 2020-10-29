/*  Muhamad Elassar
    CS1 Assignment 3: Forbidden Anagrams
    10/14/2019                   
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int forbiddenCount = 0; //count for number of forbidden words
int repeatedCount = 0; //count for number of forbidden words that consist multiple bad words
int permCount = 0; //total amount of permutations
char endResult[13]; //end result of permutated string
bool visited[12]; //array to keep track of each character we visited in the string

// permutate the string
void permutate(int index, char * str, int n, char ** badwords);

// check if the badword(s) is a substring of the permutation and increment forbiddenCount
void isForbidden(char * str, int n, char ** badwords);

int main(){
    // input string
    char s[13];

    // number of bad words
    int n;
    scanf("%s", s);
    scanf("%d", &n);

    // array to store bad words
    char *badWords[n];
    int i;
    for(i = 0; i < n; i++){
        // allocate 13 chars for each badword
        badWords[i] = (char *) malloc(13 * sizeof(char));

        // check if allocation fails
        if(badWords[i] == NULL){
            return -1;
        }
    }

    // store bad words input
    for(i = 0; i < n; i++){
        scanf("%s", badWords[i]);
    }

    // initialize result to equal input string
    for(i = 0; i<strlen(s); i++){
        endResult[i]=s[i];
    }
    endResult[strlen(s)] = '\0';

    // initialized visited array to all false
    for(i=0; i<12; i++){
        visited[i] = false;
    }

    // get all permutations of the string and check for nonforbidden words
    permutate(0, s, n, badWords);

    // subtract the forbidden count from the permutation count and add back the repeated count
    int nonForbiddenTotal = permCount - forbiddenCount + repeatedCount;
    printf("%d\n", nonForbiddenTotal);
    return 0;
}

void permutate(int index, char * str, int n, char ** badwords) {
    // if the index is the length of the string, that means were done with that permutation
    if(index == strlen(str)){
        // make end of string null char
        endResult[index] = '\0';

        // check if the permutation is forbidden 
        isForbidden(endResult, n, badwords);

        // increment permutation count
        permCount++;

        // end function
        return;
    }

    // array of bools to compare permutation chars to index of alphabet
    bool compared[26];

    int i;
    // initialize compared array to all false
    for(i = 0; i < 26; i++)
        compared[i] = false;

    // loop through each char
    for(i = 0; i < strlen(str); i++){
        // initialize a variable so that it can be checked if it matches its order in the alphabet
        int alphabetIndex = str[i] % 26;

        if(!visited[i] && !compared[alphabetIndex]){
            // set that letter of the alphabet index to true
            compared[alphabetIndex] = true;

            // set the end result characters equal to the string characters
            endResult[index] = str[i];

            // now we visited the character so set it to true
            visited[i] = true;

            // permutate the next index
            permutate(index + 1 , str, n, badwords);

            // set visited back to false after index has reached the length of the string
            visited[i] = false;
        }

    }
}

void isForbidden(char * str, int n, char ** badwords){
    int i;
    for(i = 0; i < n; i++){
        // if there is a next badword
        if(i < n - 1){

            // if the permutation contains this badword AND the next bad word 
            if((strstr(str, badwords[i]) != NULL) && (strstr(str, badwords[i+1]) != NULL)){
                // increment count for number of forbidden words that consist multiple bad words
                repeatedCount++; 
            }
        }
        // if the permutation contains this badword
        if((strstr(str, badwords[i]) != NULL)){
            // increment forbidden word count
            forbiddenCount++;
        }
    }
}