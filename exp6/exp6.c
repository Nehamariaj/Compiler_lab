#include <stdio.h>
#include <string.h>

int k = 0, i = 0, j = 0, c = 0;
char a[16], ac[20], stk[15], act[20];

void check();

int main()
{
    puts("GRAMMAR is:");
    puts("E -> E+E");
    puts("E -> E*E");
    puts("E -> (E)");
    puts("E -> id");

    puts("Enter input string:");
    scanf("%s", a);
    c = strlen(a);
    strcpy(act, "SHIFT");

    puts("\nStack\t\tInput\t\tAction");

    for (k = 0, i = 0, j = 0; j < c;)
    {
        // Shift 'id' as a whole
        if (a[j] == 'i' && a[j + 1] == 'd')
        {
            stk[i++] = a[j++];
            stk[i++] = a[j++];
            stk[i] = '\0';
            printf("\n$%s\t\t%s$\t\t%s id", stk, a + j, act);
            check();
        }
        else
        {
            stk[i++] = a[j++];
            stk[i] = '\0';
            printf("\n$%s\t\t%s$\t\t%s symbol", stk, a + j, act);
            check();
        }
    }

    // Final acceptance check
    if (strcmp(stk, "E") == 0)
        printf("\n$%s\t\t%s$\t\tACCEPT\n", stk, a + j);
    else
        printf("\nInput string rejected!\n");

    return 0;
}

void check()
{
    strcpy(ac, "REDUCE TO E");

    while (1)
    {
        // id → E
        if (i >= 2 && stk[i - 2] == 'i' && stk[i - 1] == 'd')
        {
            stk[i - 2] = 'E';
            stk[i - 1] = '\0';
            i -= 1;
            printf("\n$%s\t\t%s$\t\t%s", stk, a + j, ac);
        }

        // E+E → E
        else if (i >= 3 && stk[i - 3] == 'E' && stk[i - 2] == '+' && stk[i - 1] == 'E')
        {
            stk[i - 3] = 'E';
            stk[i - 2] = '\0';
            stk[i - 1] = '\0';
            i -= 2;
            printf("\n$%s\t\t%s$\t\t%s", stk, a + j, ac);
        }

        // E*E → E
        else if (i >= 3 && stk[i - 3] == 'E' && stk[i - 2] == '*' && stk[i - 1] == 'E')
        {
            stk[i - 3] = 'E';
            stk[i - 2] = '\0';
            stk[i - 1] = '\0';
            i -= 2;
            printf("\n$%s\t\t%s$\t\t%s", stk, a + j, ac);
        }

        // (E) → E
        else if (i >= 3 && stk[i - 3] == '(' && stk[i - 2] == 'E' && stk[i - 1] == ')')
        {
            stk[i - 3] = 'E';
            stk[i - 2] = '\0';
            stk[i - 1] = '\0';
            i -= 2;
            printf("\n$%s\t\t%s$\t\t%s", stk, a + j, ac);
        }

        else
            break; // No more reductions
    }
}
