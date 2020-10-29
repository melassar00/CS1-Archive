/*
Muhamad Elassar
10/31/2019
CS1 Assignment 4
*/
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

// recursive function to keep dividing list of names into halves until they're sorted arrays
void divideAndSort(int left, int right, char ** names);

// merges back each half made from divideAndSort function
int merge(char ** names, int leftStart, int leftEnd, int rightStart, int rightEnd);

// compares the strings against the new order array
int specialCompare(char * str1, char * str2);

// global variable for new order
char order[26];

int main() {
    char letters[26]; // input letters for new order
    int numNames; //number of names to input
    char ** names; // array of all names 

    int i;
    // take input for letters and set equal to global variable order
    for(i = 0; i < 26; i++){
        scanf("%c ", &letters[i]);
        order[i] = letters[i];
    }
    
    // take input for number of names
    scanf("%d", &numNames);

    // allocate memory for array of names
    names = (char **) malloc(sizeof(char *) * numNames);
    for(i = 0; i < numNames; i++){
        names[i] = (char *) malloc(sizeof(char) * 101);
    }
    // check if allocation fails
    if(names==NULL){
        return -1;
    }

    // take input for each name and store it in array
    for(i = 0; i < numNames; i++){
        scanf("%s", names[i]);
    }

    // begin merge sort
    divideAndSort(0, numNames, names);
    
    // loop through all names and print out new order of names
    for(i=0; i<numNames; i++){
        printf("%s\n", names[i]);
    }
    
}

void divideAndSort(int left, int right, char ** names){
    // BASE CASE
    // if the right and left overlap then get out of the function
    if(right - left <= 1){
        return;
    }

    // set checkpoints
    int leftStart = left;
    int leftEnd = (left+right)/2;
    int rightStart = leftEnd;
    int rightEnd = right;
    
    // recurse through with new checkpoints
    divideAndSort(leftStart, leftEnd, names); 
    divideAndSort(rightStart, rightEnd, names);

    // after fully divided, merge back
    merge(names, leftStart, leftEnd, rightStart, rightEnd);

}

int merge(char ** names, int leftStart, int leftEnd, int rightStart, int rightEnd) {
    // get the lengths of each half
    int leftLength = leftEnd - leftStart;
    int rightLength = rightEnd - rightStart;

    int i = 0;

    // allocate memory for each array of strings
    char ** left = (char **) malloc(sizeof(char*) * leftLength);
    for(i = 0; i < leftLength; i++){
        left[i] = (char *) malloc(sizeof(char) * 101);
    }
    // check if allocation fails
    if(left == NULL){
        return -1;
    }

    char ** right = (char **) malloc(sizeof(char*) * rightLength);
    for(i = 0; i < rightLength; i++){
        right[i] = (char *) malloc(sizeof(char) * 101);
    }
    // check if allocation fails
    if(right == NULL){
        return -1;
    }

    int j = 0, k = 0;
    // loop through the left half of the names and copy them into the left array
    for(i = leftStart; i < leftEnd; i++){
        strcpy(left[j], names[i]);
        j++;
    }

    // loop through the right half of the names and copy them into the right array
    for(i = rightStart; i < rightEnd; i++){
        strcpy(right[k], names[i]);
        k++;
    }

    // now loop through both the left half and the right half arrays
    for(i = leftStart, k = 0, j = 0; j < leftLength && k < rightLength; i++){
        // compare against order so the merge can go in the correct direction
        // if the left takes precedence, merge the left back into the original array
        if(specialCompare(left[j], right[k]) < 0) {
            strcpy(names[i], left[j]);
            j++;
        }
        // if the right takes precedence, merge the right back into the original array
        else { 
            strcpy(names[i], right[k]);
            k++;
        }
    }

    // merge all remaining names from the left into the original array
    while(j < leftLength){
        strcpy(names[i], left[j]);
        i++;
        j++;
    }

    // merge all remaining names from the right into the original array
    while(k < rightLength){
        strcpy(names[i], right[k]);
        i++;
        k++;
    }

}


int specialCompare(char * str1, char * str2){
    // first check if the 2 strings are equal to save time
    if(strcmp(str1, str2) == 0){
        return 0;
    }

    int str1len = strlen(str1);
    int str2len = strlen(str2);

    // array to keep track of what index each character in the string corresponds to in the new order
    int str1Indexes[str1len];
	int str2Indexes[str2len];
    
    int i=0,j=0;
    // if the first characters of each string are not equal, you only need to compare the first char
    if(str1[0] != str2[0]){
        // loop through new order array to find corresponding index
        for(j=0; j<26; j++){
            if(str1[0] == order[j]){
                // if the str1 character equals an order character, get the index of that order char
                str1Indexes[0] = j;
			}
            if(str2[0] == order[j]){
                // if the str1 character equals an order character, get the index of that order char
                str2Indexes[0] = j;
			}
        }
    }
    // if the first characters in the string are equal, keep looping until they aren't equal
    else {
        while(str1[i] == str2[i]){
            for(j=0; j<26; j++){
                // if the str1 character equals an order character, get the index of that order char
                if(str1[i] == order[j]){
                    str1Indexes[i] = j;
			    }
                if(str2[i] == order[j]){
                    // if the str1 character equals an order character, get the index of that order char
                    str2Indexes[i] = j;
			    }
            }
            i++;
        }
        // iterate through one more time to find the next indexes so that we can see the difference
        for(j=0; j<26; j++){
            if(str1[i] == order[j]){
                str1Indexes[i] = j;
            }
            if(str2[i] == order[j]){
                str2Indexes[i] = j;
            }
        }

    }

	int k = 0;
	while(1){
        // if we exceeded str2 length but not the str1 length and since were still in this loop, 
        // we know str1 takes precedence
        if(k >= str1len && k <= str2len){
			return -1;
		}
        // if we exceeded str1 length but not the str2 length and since were still in this loop, 
        // we know str2 takes precedence
		else if(k <= str1len && k >= str2len){
			return 1;
		}

        // if str1 is greater than str2, str2 takes precedence
		if(str1Indexes[k] > str2Indexes[k]){
			return 1;
		}
        // if str2 is greater than str1, str1 takes precedence
		else if(str1Indexes[k] < str2Indexes[k]){
			return -1;
		}
        // if they're still equal, increment k and loop again
		else if(str1Indexes[k] == str2Indexes[k]){
			k++;
			continue;
		}
	}
	
}
