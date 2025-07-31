%{
#include<stdio.h>
#include<ctype.h>

int vowels = 0;
int consonants = 0;
%}

%%

[aeiouAEIOU] {        
    vowels++;     
}

[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z] {  
    consonants++;     
}

.|\n {   
    // Do nothing for non-alphabetic characters
}

%%

int main() {
    printf("Enter input text (Ctrl+D to finish):\n");
    yylex();  // Start lexical analysis
    printf("\nTotal vowels: %d\n", vowels);
    printf("Total consonants: %d\n", consonants);
    return 0;
}
