#include <stdio.h> 
#include <string.h> 
 
int k = 0, z = 0, i = 0, j = 0, c = 0; 
char a[16], ac[20], stk[15], act[10]; 
 
void check(); 
 
void printInput() 
{ 
    // Print input string a[] without spaces 
    int idx; 
    for (idx = 0; idx < c; idx++) 
    { 
        if (a[idx] != ' ') 
            putchar(a[idx]); 
    } 
} 
 
int main() 
{ 
    puts("GRAMMAR is E->E+E \n E->E*E \n E->(E) \n E->id"); 
    puts("enter input string "); 
    scanf("%s", a); 
    c = strlen(a); 
    strcpy(act, "SHIFT->"); 
 
    puts("stack \t input \t action"); 
    for (k = 0, i = 0; j < c; k++, i++, j++) 
    { 
        if (a[j] == 'i' && a[j + 1] == 'd') 
        { 
            stk[i] = a[j]; 
            stk[i + 1] = a[j + 1]; 
            stk[i + 2] = '\0'; 
 
            a[j] = ' '; 
            a[j + 1] = ' '; 
 
            printf("\n$%s\t", stk); 
            printInput(); 
            printf("$\tSHIFT->id"); 
 
            check(); 
        } 
        else 
        { 
            stk[i] = a[j]; 
            stk[i + 1] = '\0'; 
 
            a[j] = ' '; 
 
            printf("\n$%s\t", stk); 
            printInput(); 
            printf("$\tSHIFT->symbols"); 
 
            check(); 
        } 
    } 
 
    // After all input shifted and reduced, check for ACCEPT 
    if (strcmp(stk, "E") == 0) 
    { 
        printf("\n$%s\t", stk); 
        printInput(); 
        printf("$\tACCEPT\n"); 
    } 
    else 
    { 
        printf("\nInput string rejected!\n"); 
    } 
 
    return 0; 
} 
 
void check() 
{ 
    strcpy(ac, "REDUCE TO E"); 
 
    // Reduce id -> E 
    for (z = 0; z < c; z++) 
        if (stk[z] == 'i' && stk[z + 1] == 'd') 
        { 
            stk[z] = 'E'; 
            stk[z + 1] = '\0'; 
 
            // Print reduce only if stack length > 1 or input not empty 
            if (!(strlen(stk) == 1 && strspn(a, " ") == c)) 
                printf("\n$%s\t", stk), printInput(), printf("$\t%s", ac); 
 
            j++; 
        } 
 
    // Reduce E+E -> E 
    for (z = 0; z < c; z++) 
        if (stk[z] == 'E' && stk[z + 1] == '+' && stk[z + 2] == 'E') 
        { 
            stk[z] = 'E'; 
            stk[z + 1] = '\0'; 
            stk[z + 2] = '\0'; 
 
            if (!(strlen(stk) == 1 && strspn(a, " ") == c)) 
                printf("\n$%s\t", stk), printInput(), printf("$\t%s", ac); 
 
            i = i - 2; 
        } 
 
    // Reduce E*E -> E 
    for (z = 0; z < c; z++) 
        if (stk[z] == 'E' && stk[z + 1] == '*' && stk[z + 2] == 'E') 
        { 
            stk[z] = 'E'; 
            stk[z + 1] = '\0'; 
            stk[z + 2] = '\0'; 
 
            if (!(strlen(stk) == 1 && strspn(a, " ") == c)) 
                printf("\n$%s\t", stk), printInput(), printf("$\t%s", ac); 
 
            i = i - 2; 
        } 
 
    // Reduce (E) -> E 
    for (z = 0; z < c; z++) 
        if (stk[z] == '(' && stk[z + 1] == 'E' && stk[z + 2] == ')') 
        { 
            stk[z] = 'E'; 
            stk[z + 1] = '\0'; 
            stk[z + 2] = '\0'; 
 
            if (!(strlen(stk) == 1 && strspn(a, " ") == c)) 
                printf("\n$%s\t", stk), printInput(), printf("$\t%s", ac); 
 
            i = i - 2; 
        } 
} 
