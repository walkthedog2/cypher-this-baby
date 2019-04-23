/* NOTES
    For the decoding of a cypher, consider storing the last 3 variables, and looking for
    the word 'the'.




*/

#include <stdio.h>

#include <string.h>

#define MAX 1000

char encryptCypherCycle(char key[], int offset);
char decryptCypherCycle(char key[], int offset);
char encryptCypherSub(char key[], char code[]);
char decryptCypherSub(char key[], char code[]);
char decryptCypherCycle(int offset2;);
char repairCypherCycle(char ret[]);
int bruteForce(char key[]);
void unknownSubstitution(char key[]);

int main() {

   char key[MAX] = {
      "THE CODE TO DECODE"
   };
   FILE * input;
   input = fopen("key.txt", "r");
   fgets(key, MAX, input);
   int offset = 25;
   //   char code[1024] = {"PHQGIUMEAYLNOFDXJKRCVSTZWB"};  //This is included for debugging purposes
   /*    scanf("%[^\n]s ", key);                       //It is an example of a key, for the use in a substitution cypher
       scanf("%d", &offset); */
   int i;
   int length = strlen(key);

   for (i = 0; i < length; i++) {
      if ((key[i] <= 122) && (key[i] >= 97)) {
         key[i] -= 32;
      }

   }

   printf("the text to be encoded is %s\n", key);
   printf("the length of the string is %d\n", length);
   printf("the offset of the cyper is %d\n", offset);
   unknownSubstitution(key);
}

/*------------------------------------------------------------------------------*/

char encryptCypherCycle(char key[], int offset) {
   char encrypt;
   int index;
   int length = strlen(key);

   printf("the encrypted code is: ");
   for (index = 0; index < length; index++) {

      encrypt = (key[index] + offset);

      if ((encrypt >= (32 + offset)) && (encrypt <= (64 + offset))) {
         encrypt = encrypt - offset;
         printf("%c", encrypt);
      } else if ((encrypt >= 'A') && (encrypt <= 'Z')) {
         printf("%c", encrypt);
      } else if (encrypt > 'Z') {

         encrypt = encrypt - 26;
         printf("%c", encrypt);
      } else if (encrypt < 'A') {

         encrypt = encrypt + 26;
         printf("%c", encrypt);
      }

   }
   return 0;
}

/*------------------------------------------------------------------------------*/
char decryptCypherCycle(char key[], int offset) {
   char encrypt;
   int index;
   int length = strlen(key);

   printf("the decrypted code is: ");
   for (index = 0; index < length; index++) {
      encrypt = (key[index] - offset);

      if ((encrypt >= (32 - offset)) && (encrypt <= (64 - offset))) {
         encrypt = encrypt + offset;
         printf("%c", encrypt);
      } else if ((encrypt >= 'A') && (encrypt <= 'Z')) {
         printf("%c", encrypt);
      } else if (encrypt > 'Z') {

         encrypt = encrypt - 26;
         printf("%c", encrypt);
      } else if (encrypt < 'A') {

         encrypt = encrypt + 26;
         printf("%c", encrypt);
      }

   }
   return 0;
}

/*------------------------------------------------------------------------------*/
char encryptCypherSub(char key[], char code[]) {
   int index;
   int length = strlen(key);
   int difference;

   printf("the encrypted code is: ");
   for (index = 0; index < length; index++) {

      if ((key[index] >= 32) && (key[index] <= 64)) {
         printf("%c", key[index]);
      } else if ((key[index] >= 65) && (key[index] <= 90)) {
         difference = key[index] - 65;
         key[index] = code[difference];
         printf("%c", key[index]);
      }
   }
   return 0;
}

/*------------------------------------------------------------------------------*/

char decryptCypherSub(char key[], char code[]) {

   int index;
   int length = strlen(key);

   char alphabet[30] = {
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
   };
   printf("the decrypted code is: ");
   for (index = 0; index < length; index++) {
      if ((key[index] >= 32) && (key[index] <= 64)) {
         printf("%c", key[index]);
      } else if ((key[index] >= 65) && (key[index] <= 90)) {
         int i;

         for (i = 0; i < 26; i++) {

            if (key[index] == code[i]) {
               printf("%c", alphabet[i]);
            }

         }
      }

   }
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
}

void unknownSubstitution(char key[]) {
   char alphabet[26] = {
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
   };
   char code[26] = {"--------------------------"};
   int wordcount = 0;
   int c = 0, count[26] = {
      0
   }, x, y = 0, temp;

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
      printf("%c occurs %d times in the string.\n", c + 'A', count[c]);
   }
   printf("the most common letter was %c\n", temp + 'A');
   code[4] = temp + 'A';
   
   int a, b;
   int minusOne, minusTwo, minusThree;
   for (a = 0; a <= strlen(key); a++) {
      if (key[a] == 32 || key[a] == '\0') {
         
         if ((wordcount == 3) && (minusOne == code[4])) {
            code[7] = minusTwo;
            code[20] = minusThree;
            
         
         } else if ((wordcount == 2) && ()) {
         } else {
            printf("%d ", wordcount);
            wordcount = 0;
         }

      } else {
         wordcount++;
      }
      minusThree = minusTwo;
      minusTwo = minusOne;
      minusOne = key[a];
   }
   printf("\ncode: \n");
   
   for (b = 0; b < 26; b++){
       printf("%c", code[b]);
   }

}