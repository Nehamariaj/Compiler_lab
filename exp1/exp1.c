#include <stdio.h>
#include <ctype.h>
#include <string.h>

int operator(char ch, int size, char op[]) {
    for (int i = 0; i < size; i++) {
        if (ch == op[i]) {
            return 1;
        }
    }
    return 0;
}

int search_keyword(char* word, int keyword_size, const char* keywords[]) {
    for (int i = 0; i < keyword_size; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void process_token(char* token, int length, const char* keywords[], int keyword_size) {
    if (length > 0) {
        token[length] = '\0';

        if (search_keyword(token, keyword_size, keywords)) {
            printf("%s is a keyword\n", token);
        } else if (isdigit(token[0])) {
            int is_number = 1;
            for (int i = 1; i < length; i++) {
                if (!isdigit(token[i])) {
                    is_number = 0;
                    break;
                }
            }
            if (is_number) {
                printf("%s is a number\n", token);
            } else {
                printf("%s is an invalid token\n", token);
            }
        } else {
            printf("%s is an identifier\n", token);
        }
    }
}

int main() {
    char op[] = { '+', '-', '*', '/','='};
    char alpha_num[100];
    int a = 0;
    int size = sizeof(op) / sizeof(op[0]);
    FILE* fp;
    char ch, next_ch;

    fp = fopen("sentence.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    const char* keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
        "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "restrict",
        "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", 
        "unsigned", "void", "volatile", "while"
    };
    int keyword_size = sizeof(keywords) / sizeof(keywords[0]);

    while ((ch = fgetc(fp)) != EOF) {
        if (isalnum(ch)) {
            alpha_num[a++] = ch;
        } else {
            process_token(alpha_num, a, keywords, keyword_size);
            a = 0;

            if (ch == '/') {
                next_ch = fgetc(fp);
                if (next_ch == '/') {
                    // Single-line comment
                    while ((ch = fgetc(fp)) != EOF && ch != '\n') {
                        // Skip
                    }
                } else if (next_ch == '*') {
                    // Multi-line comment
                    while ((ch = fgetc(fp)) != EOF) {
                        if (ch == '*' && (next_ch = fgetc(fp)) == '/') {
                            break;
                        }
                    }
                } else {
                    // '/' operator
                    ungetc(next_ch, fp);
                    printf("%c is an operator\n", ch);
                }
            } else if (operator(ch, size, op)) {
                printf("%c is an operator\n", ch);
            } else if (ch == ' ' || ch == '\n' || ch == '\t') {
                // Whitespace — skip
            } else {
                printf("%c is an unknown character\n", ch);
            }
        }
    }

    // Process any remaining token at the end
    process_token(alpha_num, a, keywords, keyword_size);

    fclose(fp);
    return 0;
}
