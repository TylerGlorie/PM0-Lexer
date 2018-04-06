/*
 Tyler Glorie
 N***** P*****
 COP 3402 - HW2
 INSTRUCTIONS: pass file name as argument.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//prototypes
void readFile(char* filename);
int getTokens(void);
bool isLetter(char c);
bool isNumber(char c);
bool isSpecialSymbol(char c);
bool isSpace(char c);
int getSymbolNum(char*);

//some variables
int fileLength;
char input[3000];
char tokens[1000][11];


int main(int argc, const char * argv[]) {
    
    int tokenCount = 0, i = 0;
    // Reads and stores input in array
    readFile(argv[1]);
    // Grab tokens from input and store number of tokens
    tokenCount = getTokens();
    
    if(tokenCount != -1) {
        // Print lexeme table
        printf("\n\nLexeme Table:\n");
        printf("lexeme\t\ttoken type\n");
        
        for(i = 0; i < tokenCount; i++) {
            printf("%s\t\t%d\n", tokens[i], getSymbolNum(tokens[i]));
        }
        
        // Printing lexeme list
        printf("\nLexeme List\n");
        
        for(i = 0; i < tokenCount; i++) {
            
            int x = getSymbolNum(tokens[i]);
            
            printf("%d ", x);
            
            if(x == 2) {
                printf("%s ", tokens[i]);
            }
            else if(x == 3) {
                printf("%s ", tokens[i]);
            }
        }
    }
    return 0;
}

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isNumber(char c) {
    return (c >= '0' && c <= '9');
}

bool isSpecialSymbol(char c) {
    return (c == '=' || c == '>' || c == '<' || c == ',' || c == '.' ||
            c == ';' || c == ':' || c == '+' || c == '-' || c == '*' ||
            c == '/' || c == '(' || c == ')');
}

bool isSpace(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c=='\r' || c=='\v' || c=='\f' );
}

void readFile(char* filename) {
    FILE* fp = fopen(filename, "r");
    int i = 0;
    
    if(fp == NULL) {
        printf("Error: File was not found");
        return ;
    }
    
    printf("Source Program:%s\n", filename);
    
    // Store file into input[] and print program
    while(1) {
        
        input[i] = fgetc(fp);
        if( feof(fp) ) break;
        printf("%c", input[i++]);
    }
    
    // input[fileLength - 1] holds the ending '.' character
    fileLength = i;
    
    fclose(fp);
    
}

int getTokens() {
    int i = 0, j = 0, k = 0, tokenCount = 0;
    char token[11];
    
    // Loop through file, writing into tokens[]
    while(i < fileLength) {
        // Load first char into token
        token[j++] = input[i];
        
        // Keyword or identifier
        if(isLetter(input[i])) {
            // Add continuous letters and digits to keyword / id string
            while( i < fileLength - 1 && (isLetter(input[i+1]) || isNumber(input[i+1])) ) {
                token[j++] = input[++i];
                // IDs can be 11 characters max
                if(j > 11) {
                    printf("Error: Identifier too long.");
                    return -1;
                }
            }
            
            for(k = 0; k < j; k++) {
                tokens[tokenCount][k] = token[k];
            }
            // i++ so next cycle thru while loop starts with new, unseen, untouched char
            i++;
            tokenCount++;
            
        }
        // Number of 5 digits or less
        else if(isNumber(input[i])) {
            while(i < fileLength - 1 && isNumber(input[i+1])) {
                token[j++] = input[++i];
            }
            
            // Numbers shouldn't contain letters
            if(isLetter(input[i+1])) {
                printf("Error: Invalid symbol.");
                return -1;
            }
            
            // Numbers cannot be larger than 5 digits
            if(j > 5) {
                printf("Error: Number too large.");
                return -1;
            }
            
            for(k = 0; k < j; k++) {
                tokens[tokenCount][k] = token[k];
            }
            tokenCount++;
            i++;
            
        }
        // Symbol or comments
        else if(isSpecialSymbol(input[i])) {
            switch((char)input[i]) {
                    
                case '<':
                    if(input[i+1] == '=' || input[i+1] == '>') {
                        token[j++] = input[++i];
                    }
                    for(k = 0; k < j; k++) {
                        tokens[tokenCount][k] = token[k];
                    }
                    tokenCount++;
                    i++;
                    break;
                    
                case '>':
                    if(input[i+1] == '=') {
                        token[j++] = input[++i];
                        for(k = 0; k < j; k++) {
                            tokens[tokenCount][k] = token[k];
                        }
                        tokenCount++;
                    }
                    i++;
                    break;
                    
                case '=':
                    for(k = 0; k < j; k++) {
                        tokens[tokenCount][k] = token[k];
                    }
                    tokenCount++;
                    i++;          break;
                    
                case '+':
                    for(k = 0; k < j; k++) {
                        tokens[tokenCount][k] = token[k];
                    }
                    tokenCount++;i++;          break;
                    
                case '-':
                    for(k = 0; k < j; k++) {
                        tokens[tokenCount][k] = token[k];
                    }
                    tokenCount++; i++;         break;
                    
                case ',':
                    for(k = 0; k < j; k++) {
                        tokens[tokenCount][k] = token[k];
                    }
                    tokenCount++;   i++;       break;
                    
                case '.':
                    for(k = 0; k < j; k++) {
                        tokens[tokenCount][k] = token[k];
                    }
                    tokenCount++;    i++;      break;
                    
                case '(':
                    for(k = 0; k < j; k++) {
                        tokens[tokenCount][k] = token[k];
                    }
                    tokenCount++;    i++;      break;
                    
                case ')':
                    for(k = 0; k < j; k++) {
                        tokens[tokenCount][k] = token[k];
                    }
                    tokenCount++;      i++;    break;
                    
                case ';':
                    for(k = 0; k < j; k++) {
                        tokens[tokenCount][k] = token[k];
                    }
                    tokenCount++;   i++;       break;
                    
                case ':':
                    if(input[i+1] == '=') {
                        token[j++] = input[++i];
                    }
                    for(k = 0; k < j; k++) {
                        tokens[tokenCount][k] = token[k];
                    }
                    tokenCount++;     i++;     break;
                    
                case '/':
                    // Skip all content between comment symbols
                    if(input[i+1] == '*') {
                        i++;
                        
                        while(input[++i] != '*') {
                            if(input[i+1] == '/') {
                                i++;
                                break;
                            }
                        }
                    }
                    else if(input[i+1] == '/') {
                        i++;
                        
                        while(input[++i] != '\n') {
                            i++;
                        }
                    }
                    // else it's just a div symbol
                    else {
                        for(k = 0; k < j; k++) {
                            tokens[tokenCount][k] = token[k];
                        }
                        tokenCount++;
                        i++;
                        break;
                    }
            }
        }
        // Ignore and skip spaces
        else if(isSpace(input[i])) {
            i++;
        }
        // Return error for invalid symbol
        else {
            printf("Error: Invalid symbol.");
            return -1;
        }
        
        j = 0;
    }
    
    return tokenCount;
}

//return symbol number
int getSymbolNum(char* string){
    if(strcmp(string, "\0") == 0) {return 1;}
    else if (strcmp(string, "+") == 0) {return 4;}
    else if (strcmp(string, "-") == 0) {return 5;}
    else if (strcmp(string, "*") == 0) {return 6;}
    else if (strcmp(string, "/") == 0) {return 7;}
    else if (strcmp(string, "%") == 0) {return 8;}
    else if (strcmp(string, "=") == 0) {return 9;}
    else if (strcmp(string, "<>") == 0) {return 10;}
    else if (strcmp(string, "<") == 0) {return 11;}
    else if (strcmp(string, "<=") == 0) {return 12;}
    else if (strcmp(string, ">") == 0) {return 13;}
    else if (strcmp(string, ">=") == 0) {return 14;}
    else if (strcmp(string, "(") == 0) {return 15;}
    else if (strcmp(string, ")") == 0) {return 16;}
    else if (strcmp(string, ",") == 0) {return 17;}
    else if (strcmp(string, ";") == 0) {return 18;}
    else if (strcmp(string, ".") == 0) {return 19;}
    else if (strcmp(string, ":=") == 0) {return 20;}
    else if (strcmp(string, "begin") == 0) {return 21;}
    else if (strcmp(string, "end") == 0) {return 22;}
    else if (strcmp(string, "if") == 0) {return 23;}
    else if (strcmp(string, "then") == 0) {return 24;}
    else if (strcmp(string, "while") == 0) {return 25;}
    else if (strcmp(string, "do") == 0) {return 26;}
    else if (strcmp(string, "call") == 0) {return 27;}
    else if (strcmp(string, "const") == 0) {return 28;}
    else if (strcmp(string, "var") == 0) {return 29;}
    else if (strcmp(string, "procedure") == 0) {return 30;}
    else if (strcmp(string, "write") == 0) {return 31;}
    else if (strcmp(string, "read") == 0) {return 32;}
    else if (strcmp(string, "else") == 0) {return 33;}
    else if(isLetter(string[0])){return 2;}
    else if(isNumber(string[0])){return 3;}
    else{return -1;}
}
