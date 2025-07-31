%{
int lines = 0;
int words = 0;
int chars = 0;
int nums  = 0;
int in_word=0;
%}

%%

\n   { 
    lines++; 
    chars++; 
    in_word=0;
}

[ \t] {
    chars++; 
    in_word=0;
}

[a-zA-Z_] {
    chars++;
    if(!in_word){
        words++;
        in_word = 1;
    }
}

[0-9] {
    chars++;
    nums++;
    if (!in_word) {
        words++;
        in_word = 1;
    }
}

. { 
    chars++; 
    in_word=0;
}

%%

int yywrap() {
    return 1;
}

int main() {
    
    FILE *fp = fopen("inp2_2.txt", "r");
    if (!fp) {
        perror("Failed to open file");
        return 1;
    }
        
    yyin = fp;    
    
    yylex();

    printf("Lines: %d\n", lines);
    printf("Words: %d\n", words);
    printf("Characters: %d\n", chars);
    printf("Numbers: %d\n", nums);
    
    // Close the file
    fclose(fp);
    
    return 0;
}

