/* NOTES
    PUT THE TEXT TO BE DECODED IN KEY.txt
    PUT ANY SUBSTITUION KEYS IN CODE.txt
    Github commits may be in a confusing order because I was originally saving each required commit as a new main.c file
    Somewhere in the backlog are the requirements for that section
        Sorry for any confusion!!!!!
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024 //This sets
/*-----------------------------------------------*/
//The respective functions of the program
/*-----------------------------------------------*/
char encryptCypherCycle(char key[], int offset);
char decryptCypherCycle(char key[], int offset);
char encryptCypherSub(char key[], char code[]);
char decryptCypherSub(char key[], char code[]);
char decryptCypherCycle(int offset2;);
char repairCypherCycle(char ret[]);
int bruteForce(char key[]);
void unknownSubstitution(char key[]);
int levenshtein(char *s, char *t);
/*-----------------------------------------------*/
int main() {
    char key[MAX]; //Key is the defined string to be encoded and decoded
   FILE * input;
   input = fopen("key.txt", "r");
   fgets(key, MAX + 1, input);
   
    char code[26]; //Code is the substitution cypher encoding key (sorry about the reverse terminology!)
   FILE * iinput;
   iinput = fopen("code.txt", "r");
   fgets(code, 27, iinput);
   
   int offset; //Offset is used for the movement of a caeser cypher
/*-----------------------------------------------*/
//This section changes any lower-case letters into their respective upper-case counterparts
   int i;
   for (i = 0; i < strlen(key); i++) {
      if ((key[i] <= 122) && (key[i] >= 97)) {
         key[i] -= 32;
      }
   }
 /*-----------------------------------------------*/
int menu = 0, secondary = 0; //Menu and secondary menu, uses integer input to decide which function to execute
   printf("Welcome to the Cypher program\n");
   printf("For the decoding of a cypher, press 1, or for the encoding of cypher text, press 2\n");
   scanf("%d", &menu);
   if (menu == 1) {
       printf("For decoding a caeser cypher with a known rotation, press 1\nFor the decoding of a known substitution cypher, press 2\nFor the brute forcing of an unknown caeser cypher, press 3\nFor the decoding of an unknown substitution cypher, press 4\n");
       scanf("%d", &secondary);
       if (secondary == 1) {
           printf("What offset are you using? (0 - 25)\n");
           scanf("%d", &offset);
           if (offset > 25 || offset < 0){
               printf("incorrect input for the offset\n");
           }
           encryptCypherCycle(key, offset);
       } else if (secondary == 2) {
           decryptCypherSub(key, code);
       } else if (secondary == 3) {
           bruteForce(key);
       } else if (secondary == 4) {
           unknownSubstitution(key);
       } else {
           printf("error: no input\n");
       }
       } else if (menu == 2) {
       printf("For encoding using a rotation cypher, press 1, else for the encoding of a substitution cypher, press 2\n");
       scanf("%d", &secondary);
       if (secondary == 1){
           printf("What offset are you using? (0 - 25)\n");
           scanf("%d", &offset);
           if (offset > 25 || offset < 0){
               printf("incorrect input for the offset\n");
           }
           encryptCypherCycle(key, offset);
       } else if (secondary == 2) {
           encryptCypherSub(key, code);
       } else {
           printf("error: no input\n");
       }
   } else {
       printf("error: no input\n");
   }
/*debugging and statistical text 
   printf("the text to be encoded is %s\n", key);
   printf("the length of the string is %d\n", length);
   printf("the offset of the cyper is %d\n", offset); */
}

/*------------------------------------------------------------------------------*/
//This function changes the stored string 'key' as directed by the offset
char encryptCypherCycle(char key[], int offset) {
   int index;
   int length = strlen(key);

   printf("the encrypted code is:     ");
   for (index = 0; index < length; index++) { //For the entire length of the string
      if ((key[index] >= ' ') && (key[index] < 'A')) { //If the string is anything except a letter, then it remains the same
         key[index] = key[index];
      } else if ((key[index] >= 'A') && (key[index] <= 'Z')) { //If the string is a capital letter, add the offset
         key[index] += offset;
      }
      if (key[index] > 'Z') { //If it reaches beyond Z, loop it back to the start of the alphabet
         key[index] -= 26;
      }
   }
   printf("%s", key); //print the key to the terminal
   return 0;
}

/*------------------------------------------------------------------------------*/
char decryptCypherCycle(char key[], int offset) {
   int index;
   int length = strlen(key);

   printf("the decrypted code is: ");
   for (index = 0; index < length; index++) { //for the entire length of the string
      if ((key[index] >= ' ') && (key[index] < 'A')) { //If the string is anything except a letter, then it remains the same
         key[index] = key[index];
      } else if ((key[index] >= 'A') && (key[index] <= 'Z')) { //If the string is a capital letter, subtract the offset
         key[index] -= offset;
         if (key[index] < 'A') { //If it reaches below A, loop it back to the start of the alphabet
             key[index] += 26;
         }
      }
   }
   printf("%s", key); //print the key to the terminal
   return 0;
}

/*------------------------------------------------------------------------------*/
char encryptCypherSub(char key[], char code[]) {
   int index;
   int length = strlen(key);
   int difference;

   printf("the encrypted code is:     ");
   for (index = 0; index < length; index++) { //for the entire length of the string
      if ((key[index] >= 32) && (key[index] < 'A')) { //If the string is anything except a letter, then it remains the same
         key[index] = key[index];
      } else if ((key[index] >= 'A') && (key[index] <= 'Z')) { //If the string is a capital letter
         difference = key[index] - 'A'; //Difference is the number of the alphabet that the letter is from (0- 25)
         key[index] = code[difference]; //This corresponds to the same letter on the code string (0-25)
      }
   }
   printf("%s", key); //print the key to terminal
   return 0;
}

/*------------------------------------------------------------------------------*/

char decryptCypherSub(char key[], char code[]) {
   int index, i;
   int length = strlen(key);

   char alphabet[30] = {
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
   };
   printf("the decrypted code is:    ");
   for (index = 0; index < length; index++) { //For the entire length of the string
      if ((key[index] >= ' ') && (key[index] < 'A')) { //If the string is anything except a letter, then it remains the same
         key[index] = key[index];
      } else if ((key[index] >= 65) && (key[index] <= 90)) { //If the string is a capital letter
         for (i = 0; i < 26; i++) { //This matches the letter to its position on the code string
            if (key[index] == code[i]) { //when it's equivalent
               key[index] = alphabet[i]; //it changes the letter to the respective letter on the alphabet
            }
         }
      }
   }
   printf("%s\n", key); //print the key to the terminal
   return 0;
}

/*------------------------------------------------------------------------------*/
int bruteForce(char key[]) {
   char stringDest[MAX];
   char space[20] = " .,\n";
   char word2[512];
   int count, wordcount = 1, index, i, rotate, movement = 0;
   
   for (count = 0; key[count] != '\0'; count++) { //For the length of the string, i.e. before it reaches the return key '\0'
      if (key[count] == ' ')
         wordcount++;
   } //This function is mostly used for debugging, it returns the length of the string

   FILE * dictionary;
   dictionary = fopen("dictionary.txt", "rt"); //open the dictionary file

printf("the decrypted text is:    ");
   for (i = 0; i < 26; i++) { //begins at 0, not rotating the code yet from its original, but for each iteration that doesn't return something readable, it will increase the offset by 1
      movement = 0;
      for (rotate = 0; rotate < strlen(key); rotate++) {

         if ((key[rotate] >= 32) && (key[rotate] < 64)) {
            key[rotate] = key[rotate];
         } else if ((key[rotate] < 90) && (key[rotate] >= 65)) {
            key[rotate]++;
         } else if (key[rotate] == 90) {
            key[rotate] -= 25;
         }
      }

      strcpy(stringDest, key); //copies the rotated key to stringDest in order to to not mess up the original string

      char * retrn = strtok(stringDest, space);
      
      while (movement < 10) { //this was originally (retrn != NULL) but it would often repeat the decoded text multiple times, this runs the function for the first 10 words
         for (index = 0; index < 9898; index++) { //scans the dictionary for the entire word
            fscanf(dictionary, "%s", word2);
            if ((strcmp(retrn, word2)) == 0) { //If the words are equivalent, i.e. it is readable
               printf("%s\n", key); //print the key, as it has been rotated correctly
               return 0; //end the function
            }

         }
         rewind(dictionary); //rewind the dictionary file to the start
         retrn = strtok(NULL, space); //restart the next string token at the next NULL position
         movement++; //Increase movement by 1, for a maximum of 10
      }
   }
   return 0;
}

void unknownSubstitution(char key[]) {
   char code[100] = {"                                     "}; //sets the code to a blank slate
   int wordcount = 0;
   
   int c = 0, count[26] = {0}, x, y = 0, temp;
   
   while (key[c] != '\0') { //a function that finds the letter count
      if (key[c] >= 'A' && key[c] <= 'Z') { //if the character is a capital letter
         x = key[c] - 'A'; //sets x to its position on the alphabet
         count[x]++; //increases the count for that letter on the respective array position
    }

      c++; //moves the index along
   }

   for (c = 0; c < 26; c++) { //this funtion finds the most frequent character
      if (count[c] > y) { //if the count for that letter is greater than the greatest one previously
         y = count[c]; //change y to that count number
         temp = c; //store the letter in temp
      }
   }
   printf("the most common letter was %c\n", temp + 'A'); //this is mostly just for debugging
   code[4] = temp + 'A'; //sets the most frequent letter to e on the code array
  
   int a, minusOne, minusTwo, minusThree, minusFour, minusFive, minusSix, threeCount = 0, determinantOne, determinantTwo, counterOne = 0, counterTwo = 0, additive = 0;
 
   for (a = 0; a <= strlen(key); a++) { //for the length of the array
      if (key[a] == ' ' || key[a] == '\0') {    //If the end of the word is reached, i.e. a space character or the end of the string
         if ((wordcount == 3) && (minusOne == code[4])) { // This function assumes for the word THE, searching for a three letter word ending in E
            code[7] = minusTwo; //H
            code[19] = minusThree; //T
            wordcount = 0; //reset word count
            threeCount++; //Adds to the three letter word counter
        } else if ((wordcount == 5) && (minusOne == code[7]) && (minusFour == code[7])) { //W H  I   C    H
             code[2] = minusTwo; //C
             code[22] = minusFive; //W
             wordcount = 0; //reset word count
        } else if ((minusOne == code[19]) && (minusTwo == code[7])) { //words ending in GHT
             code[6] = minusThree; //G
             wordcount = 0; //reset word count
        } else if ((minusOne == code[17]) && (minusTwo == code[4]) && (minusFour == code[4])) { //ending in EVER
             code[21] = minusThree; //V
             wordcount = 0; //reset word count
        } else if ((wordcount == 3) && (minusOne == minusThree)) { //D I  D
             code[3] = minusOne; //D
             wordcount = 0; //reset word count
        } else if ((wordcount == 7) && (minusOne == code[4]) && (minusSix == code[4])) { //B E  C   A    U     S      E
             code[21] = minusThree; //U
             code[19] = minusTwo; //S
             wordcount = 0; //reset word count
        } else if ((wordcount == 2) && (minusTwo == code[19])) { //Assumes for the word TO, searching for a two letter word beginning with T
             code[14] = minusOne; //O
             wordcount = 0; //reset word count
        } else if ((wordcount == 2) && (minusTwo == code[14])) { //OF
             code[5] = minusOne; //F
             wordcount = 0; //reset word count
         } else if (wordcount == 1) { //Determines the letters I and A
             if (additive == 0) { //This function runs once
                 determinantOne = minusOne; //For debugging, determinantOne == 'I'
                 counterOne++;
                 additive++;
             } else if (minusOne == determinantOne) { //These exist to differentiate between the two single letter words, I and A.
                 determinantOne = minusOne; //This gives one of the values to determinantTwo, either I or A. For testing purposes I has been assigned determinantTwo
                 counterOne++; //Adds one to a counter which will assume the most used one to be A
             } else if ((minusOne != determinantOne) || (minusOne == determinantTwo)) { //If they are equal, i.e. the same one letter word has been used since last occurence. //the other 
                 determinantTwo = minusOne;
                 counterTwo++;
             }
             wordcount = 0;
         } else {
             wordcount = 0;
         }
      } else { //if a space isnt reached, increase the word count
         wordcount++;
      }
//the variables that allow the back tracking of letters are moved forward
      minusSix = minusFive;
      minusFive = minusFour;
      minusFour = minusThree;
      minusThree = minusTwo;
      minusTwo = minusOne;
      minusOne = key[a];
   }
   if (counterTwo >= counterOne) { //Finds which single letter is equal to I
       code[0] = determinantTwo;
       code[8] = determinantOne;
   } else if (counterOne > counterTwo) {
       code[0] = determinantOne;
       code[8] = determinantTwo;
   }
//prints what is decoded so far
   //printf("\ncode: nwlrbmqhcdazokyitxjfegpsvu");  this section is for debugging with a test substitution cypher
   printf("\ncode: ABCDEFGHIJKLMNOPQRSTUVWXYZ");
   printf("\ncode: ");
   
   printf("%s\n\n", code);
decryptCypherSub(key, code); //runs the substitution cypher with what has been determined from the code so far


//NOTES
//From herein I tried to create a function that would assume similiarities between words based on the 'levenshtein edit distance' and what was worked out so far
//It worked for a while with decent results but I ran out of time because the assignment had to be submitted
//If there's an obvious mistake that I've missed could you please email me @: thwaitessebastian1@gmail.com
//I've changed a few things during debugging that might have broken it  :)

/*
FILE * dictionary;
dictionary = fopen("dictionary.txt", "rt");

char storage[512];
strcpy(storage, key);

const char space[20] = {" ,."};
char * s1 = strtok(key, space);
char s2[512];
int i, b = 0, differential, wordcount2 = 0;
printf("\n");
wordcount = 0;
c = 0;
char alphabet[26] ={"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

while (s1 != NULL) {
    
    strcpy(storage, s1);
    for (i=0; i<strlen(s1); i++) {
        wordcount++;
    }
        for (i = 0; i < 9897; i++) {
            fscanf(dictionary, "%s", s2);
            
            if (strcmp(s1, s2) == 0) {
                printf("%s ", s1);
                differential = 1;
                break;
            }
            
            for (a=0; a<strlen(s2); a++) { //finds the length of the dictionary word, appropriate for length comparison
                wordcount2++;
            }
            
            if ((levenshtein(s1, s2) == 1) && (wordcount2 == wordcount)) { //if one letter or less can be changed to make the word in the dictionary.
                for (a = 0; a < wordcount; a++) {
                    for (b = 0; b < 26; b++) {
                        if ((alphabet[b] == s1[a]) && (code[b] != ' ')) {
                            storage[a] = s1[a];
                        } 
                        if ((alphabet[b] == s1[a]) && (code[b] == ' ')) {
                            storage[a] = s2[a];
                        }
                    }
                }
                break;
            }
            wordcount2 = 0;
        }
        }
        printf("%s", storage);
    s1 = strtok(NULL, space);
    differential = 0;
    wordcount=0;
    wordcount2 = 0;
    c=0; 
    */
} 

//returns the levenshtein edit distance
int levenshtein(char *s, char *t) {
	int ls = strlen(s), lt = strlen(t);
	int d[ls + 1][lt + 1];
 
	for (int i = 0; i <= ls; i++)
		for (int j = 0; j <= lt; j++)
			d[i][j] = -1;
 
	int dist(int i, int j) {
		if (d[i][j] >= 0) return d[i][j];
 
		int x;
		if (i == ls)
			x = lt - j;
		else if (j == lt)
			x = ls - i;
		else if (s[i] == t[j])
			x = dist(i + 1, j + 1);
		else {
			x = dist(i + 1, j + 1);
 
			int y;
			if ((y = dist(i, j + 1)) < x) x = y;
			if ((y = dist(i + 1, j)) < x) x = y;
			x++;
		}
		return d[i][j] = x;
	}
	return dist(0, 0);
}
