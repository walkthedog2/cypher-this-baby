/* NOTES
    For the decoding of a cypher, consider storing the last 3 variables, and looking for
    the word 'the'.




*/
#include <stdio.h>
#include <string.h>
#define MAX 1000

int lengthString(char key[]);                      /* this function returns the length of the string using strlen which is included in string.h */
char encryptCypherCycle(char key[], int offset);
char decryptCypherCycle(char key[], int offset);
char encryptCypherSub(char key[], char code[]);
char decryptCypherSub(char key[], char code[]);
char bruteForce(char key[]);

int main() {
    
    char key[MAX]; // = {"FGHIJKLMNOPQRSTUVWXYZ"};
     FILE *input;
    input = fopen("key.txt", "r");
    fgets(key, MAX, input); 
    int offset = 25;
    char code[1024] = {"PHQGIUMEAYLNOFDXJKRCVSTZWB"}; 
/*    scanf("%[^\n]s ", key);
    scanf("%d", &offset); */
    int i;
    int length = strlen(key);
        for(i = 0; i < length; i++) {
            if ((key[i] <= 122) && (key[i] >= 97)) {
                key[i] -= 32;
            }
        
        }
   
    
        printf("the text to be encoded is %s\n", key);
        printf("the length of the string is %d\n", lengthString(key));
        printf("the offset of the cyper is %d\n", offset);
    encryptCypherCycle(key, offset);
}

int lengthString(char key[]) {
    int length = strlen(key);

return length;
}


/*------------------------------------------------------------------------------*/

char encryptCypherCycle(char key[], int offset) {
    char encrypt;
    int index;
    int length = lengthString(key);
    
    printf("the encrypted code is: ");  
        for(index = 0; index < length; index++) {
            
            encrypt = (key[index] + offset);
        
        if ((encrypt >= (32 + offset)) && (encrypt <= (64 + offset))) {
                encrypt = encrypt - offset;
                printf("%c", encrypt);
            }
            else if ((encrypt >= 'A') && (encrypt <= 'Z')) {
                printf("%c", encrypt);
            }
            else if (encrypt > 'Z') {
                
                encrypt = encrypt - 26;
                printf("%c", encrypt);
            }
            else if (encrypt < 'A') {
            
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
    int length = lengthString(key);
    
    printf("the decrypted code is: ");
    for(index = 0; index < length; index++) {
        encrypt = (key[index] - offset);
        
        if ((encrypt >= (32 - offset)) && (encrypt <= (64 - offset))) {
                encrypt = encrypt + offset;
                printf("%c", encrypt);
            }
            else if ((encrypt >= 'A') && (encrypt <= 'Z')) {
                printf("%c", encrypt);
            }
            else if (encrypt > 'Z') {
                
                encrypt = encrypt - 26;
                printf("%c", encrypt);
            }
            else if (encrypt < 'A') {
            
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
    for(index = 0; index < length; index++) {
        
        if ((key[index] >= 32) && (key[index] <= 64)) {
            printf("%c", key[index]);
        }
        else if ((key[index] >= 65) && (key[index] <= 90)) {
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

    char alphabet[30] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    printf("the decrypted code is: ");
    for(index = 0; index < length; index++) {
        if ((key[index] >=32) && (key[index] <= 64)) {
            printf("%c", key[index]);
        }
        else if ((key[index] >= 65) && (key[index] <= 90)) {
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
char bruteForce (char key[]) {
    int index;
    int i;
    for (i = 0; i < 26; i++) {
        
        
        
    }
    
    
}












