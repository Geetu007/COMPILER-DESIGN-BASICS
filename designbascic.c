#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LEN 100

// List of keywords
const char *keywords[] = {"int", "float", "return", "if", "else", "while", "for", "do", "break", "continue"};
const int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

// Function to check if a word is a keyword
int isKeyword(const char *word) {
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '>' || c == '<');
}

// Lexical analysis function
void lexicalAnalyzer(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }
    
    char token[MAX_TOKEN_LEN];
    int index = 0;
    char ch;
    
    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch)) {
            continue;
        } else if (isalpha(ch)) {
            index = 0;
            while (isalnum(ch)) {
                token[index++] = ch;
                ch = fgetc(file);
            }
            token[index] = '\0';
            ungetc(ch, file);
            if (isKeyword(token)) {
                printf("Keyword: %s\n", token);
            } else {
                printf("Identifier: %s\n", token);
            }
        } else if (isdigit(ch)) {
            index = 0;
            while (isdigit(ch)) {
                token[index++] = ch;
                ch = fgetc(file);
            }
            token[index] = '\0';
            ungetc(ch, file);
            printf("Number: %s\n", token);
        } else if (isOperator(ch)) {
            printf("Operator: %c\n", ch);
        } else {
            printf("Symbol: %c\n", ch);
        }
    }
    
    fclose(file);
}

int main() {
    char filename[100];
    printf("Enter the filename: ");
    scanf("%s", filename);
    lexicalAnalyzer(filename);
    return 0;
}
