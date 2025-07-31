%{
#include <stdio.h>
#include <ctype.h>
extern FILE *yyin;  // Declare yyin for input
%}

%%

[a-z] {
    char c = toupper(yytext[0]);  // Convert lowercase to uppercase
    putchar(c);  // Print the uppercase letter
}

[A-Z] {
    char c = tolower(yytext[0]);  // Convert uppercase to lowercase
    putchar(c);  // Print the lowercase letter
}

.|\n {
    putchar(yytext[0]);  // Print any other character as it is (including digits, punctuation)
}

%%

int main() {
    FILE *fp = fopen("inp2_3.txt", "r");
    if (!fp) {
        perror("Failed to open file");
        return 1;
    }

    yyin = fp;  // Set the input stream to the file
    yylex();  // Start lexical analysis
    fclose(fp);  // Close the file after processing
    return 0;
}

