/* NOTES
    For the decoding of a cypher, consider storing the last 3 variables, and looking for
    the word 'the'.




*/

#include <stdio.h>
#include <string.h>

#define MAX 1024

char encryptCypherCycle(char key[], int offset);
char decryptCypherCycle(char key[], int offset);
char encryptCypherSub(char key[], char code[]);
char decryptCypherSub(char key[], char code[]);
char decryptCypherCycle(int offset2;);
char repairCypherCycle(char ret[]);
int bruteForce(char key[]);
void unknownSubstitution(char key[]);
int levenshtein(char *s, char *t);

int main() {
    char key[MAX];
   FILE * input;
   input = fopen("key.txt", "r");
   fgets(key, MAX, input);
   
    char code[26];
   FILE * iinput;
   iinput = fopen("code.txt", "r");
   fgets(code, 27, iinput);
   int offset = 25;
   
   
   
   /*    scanf("%[^\n]s ", key);                       //It is an example of a key, for the use in a substitution cypher
       scanf("%d", &offset); */
   int i;
   for (i = 0; i < strlen(key); i++) {
      if ((key[i] <= 122) && (key[i] >= 97)) {
         key[i] -= 32;
      }
   }
int length = strlen(key);
   printf("Welcome to the Cypher program\n");

   printf("the text to be encoded is %s\n", key);
   printf("the length of the string is %d\n", length);
   printf("the offset of the cyper is %d\n", offset);
    
  unknownSubstitution(key);
}

/*------------------------------------------------------------------------------*/

char encryptCypherCycle(char key[], int offset) {
   int index;
   int length = strlen(key);

   printf("the encrypted code is:     ");
   for (index = 0; index < length; index++) {
      if ((key[index] >= ' ') && (key[index] < 'A')) {
         key[index] = key[index];
      } else if ((key[index] >= 'A') && (key[index] <= 'Z')) {
         key[index] += offset;
      }
      if (key[index] > 'Z') {
         key[index] -= 26;
      }
   }
   printf("%s", key);
   return 0;
}

/*------------------------------------------------------------------------------*/
char decryptCypherCycle(char key[], int offset) {
   int index;
   int length = strlen(key);

   printf("the decrypted code is: ");
   for (index = 0; index < length; index++) {
      

      if ((key[index] >= ' ') && (key[index] < 'A')) {
         key[index] = key[index];
      } else if ((key[index] >= 'A') && (key[index] <= 'Z')) {
         key[index] -= offset;
         if (key[index] < 'A') {
             key[index] += 26;
         }
      }
   }
   printf("%s", key);
   return 0;
}

/*------------------------------------------------------------------------------*/
char encryptCypherSub(char key[], char code[]) {
   int index;
   int length = strlen(key);
   int difference;

   printf("the encrypted code is:     ");
   for (index = 0; index < length; index++) {

      if ((key[index] >= 32) && (key[index] < 'A')) {
         key[index] = key[index];
      } else if ((key[index] >= 'A') && (key[index] <= 'Z')) {
         difference = key[index] - 'A';
         key[index] = code[difference];
      }
   }
   printf("%s", key);
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
   for (index = 0; index < length; index++) {
      if ((key[index] >= ' ') && (key[index] < 'A')) {
         key[index] = key[index];
      } else if ((key[index] >= 65) && (key[index] <= 90)) {
         for (i = 0; i < 26; i++) {
            if (key[index] == code[i]) {
               key[index] = alphabet[i];
            }
         }
      }
   }
   printf("%s\n", key);
   return 0;
}

/*------------------------------------------------------------------------------*/
int bruteForce(char key[]) {
   char stringDest[MAX];
   char space[20] = " .,\n";
   char word2[512];
   int count, wordcount = 1, index, i, rotate, movement;
   
   for (count = 0; key[count] != '\0'; count++) {
      if (key[count] == ' ')
         wordcount++;
   }
   printf("the word count is %d\n", wordcount);

   FILE * dictionary;
   dictionary = fopen("dictionary.txt", "rt");

printf("the decrypted text is:    ");
   for (i = 0; i < 26; i++) {
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

      strcpy(stringDest, key);

      char * retrn = strtok(stringDest, space);

      while (movement < 10) { //this was originally (retrn != NULL) but it would often repeat the decoded text multiple times

         for (index = 0; index < 9898; index++) {
            fscanf(dictionary, "%s", word2);

            if ((strcmp(retrn, word2)) == 0) {

               printf("%s\n", key);
               return 1;
            }

         }
         rewind(dictionary);
         retrn = strtok(NULL, space);
         movement++;
      }
   }
   return 0;
}

void unknownSubstitution(char key[]) {
   char code[100] = {"                                     "};
   int wordcount = 0;
   
   int c = 0, count[26] = {0}, x, y = 0, temp;

   while (key[c] != '\0') {

      if (key[c] >= 'A' && key[c] <= 'Z') {
         x = key[c] - 'A';
         count[x]++;
    }

      c++;
   }

   for (c = 0; c < 26; c++) {
      if (count[c] > y) {
         y = count[c];
         temp = c;
      }
   }
   printf("the most common letter was %c\n", temp + 'A');
   code[4] = temp + 'A';
  
   int a;
   int minusOne, minusTwo, minusThree, minusFour, minusFive, minusSix, threeCount = 0, determinantOne, determinantTwo, counterOne = 0, counterTwo = 0, additive = 0;
 
   for (a = 0; a <= strlen(key); a++) {
      if (key[a] == ' ' || key[a] == '\0') {    //If the end of the word is reached, i.e. a space character or the end of the string
         if ((wordcount == 3) && (minusOne == code[4])) { // This function assumes for the word THE, searching for a three letter word ending in E
            code[7] = minusTwo; //H
            code[19] = minusThree; //T
            wordcount = 0;
            threeCount++; //Adds to the three letter word counter
        } else if ((wordcount == 3) && (minusTwo == code[14])) { //Y O  U
             code[17] = minusThree; //Y
             code[12] = minusOne; //U
             wordcount = 0;
        } else if ((wordcount == 5) && (minusOne == code[7]) && (minusFour == code[7])) { //W H  I   C    H
             code[2] = minusTwo; //C
             code[22] = minusFive; //W
             wordcount = 0;
        } else if ((minusOne == code[19]) && (minusTwo == code[7])) { //words ending in GHT
             code[6] = minusThree; //G
             wordcount = 0;
        } else if ((minusOne == code[17]) && (minusTwo == code[4]) && (minusFour == code[4])) { //ending in EVER
             code[21] = minusThree; //V
             wordcount = 0;
        } else if ((wordcount == 3) && (minusOne == minusThree)) { //D I  D
             code[3] = minusOne; //D
             wordcount = 0;
        } else if ((wordcount == 7) && (minusOne == code[4]) && (minusSix == code[4])) { //B E  C   A    U     S      E
             code[21] = minusThree; //U
             code[19] = minusTwo;
             wordcount = 0;
        } else if ((wordcount == 2) && (minusTwo == code[19])) { //Assumes for the word TO, searching for a two letter word beginning with T
             code[14] = minusOne; //O
             wordcount = 0;
        } else if ((wordcount == 2) && (minusTwo == code[14])) { //OF
             code[5] = minusOne; //F
             wordcount = 0;
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
      } else {
         wordcount++;
      }
      minusSix = minusFive;
      minusFive = minusFour;
      minusFour = minusThree;
      minusThree = minusTwo;
      minusTwo = minusOne;
      minusOne = key[a];
   }
   if (counterTwo >= counterOne) {
       code[0] = determinantTwo;
       code[8] = determinantOne;
   } else if (counterOne > counterTwo) {
       code[0] = determinantOne;
       code[8] = determinantTwo;
   }

   printf("\ncode: nwlrbmqhcdazokyitxjfegpsvu");
   printf("\ncode: ABCDEFGHIJKLMNOPQRSTUVWXYZ");
   printf("\ncode: ");
   
   printf("%s\n\n", code);
decryptCypherSub(key, code);

FILE * dictionary;
dictionary = fopen("dictionary.txt", "rt");

/* const char space[20] = {" ,."};
char * retrn = strtok(key, space);


int i, index, change;
int wordcount2 = 0;
wordcount = 0;
char word2[512];
while (retrn != NULL) {
    for (i = 0; i < strlen(retrn); i++) {
        wordcount++;
    }
    for (i = 0; i < 9897; i ++) {
        fscanf(dictionary, "%s", word2);
        
        for (index = 0; index < strlen(word2); index++){
            wordcount2++;
        }
        
        if (wordcount2 == wordcount) {
            printf("%s ", word2);
            change = 1;
            break;
        }
        wordcount2 = 0;
    }
    if (change != 1) {
            printf("%s ", retrn);
        }
    
    retrn = strtok(NULL, space);
    change = 0;
    wordcount = 0;
    wordcount2 = 0;
}
*/



char storage[512];
strcpy(storage, key);

const char space[20] = {" ,."};
char * s1 = strtok(key, space);
char s2[512];
int i, b = 0, differential, wordcount2 = 0, justify = 0;
printf("\n");
char condition[512] = {"000000000000000000000000000000000000000000000000"};
wordcount = 0;
temp = 0;
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
            
            if ((levenshtein(s1, s2) <= 2) && (wordcount2 == wordcount)) { //if one letter or less can be changed to make the word in the dictionary.
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
            }
            wordcount2 = 0;
        }
            
        }
        if (differential != 1) {
            printf("%s ", storage);
        }

        
    s1 = strtok(NULL, space);
    differential = 0;
    wordcount=0;
    wordcount2 = 0;
    justify = 0;
    temp++;
    c=0;
} 


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
