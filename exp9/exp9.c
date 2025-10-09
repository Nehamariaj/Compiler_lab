#include <stdio.h>
#include <string.h>

int main() {
    char op[2], arg1[5], arg2[5], result[5];
    FILE *fp1, *fp2;
    char f[100];

    printf("Enter input file name: ");
    fgets(f, sizeof(f), stdin);
    f[strcspn(f, "\n")] = 0;  // Remove trailing newline

    fp1 = fopen(f, "r");
    if (fp1 == NULL) {
        perror("Error opening input file");
        return 1;
    }

    fp2 = fopen("output.txt", "w");
    if (fp2 == NULL) {
        perror("Error opening output file");
        fclose(fp1);
        return 1;
    }

    while (fscanf(fp1, "%s %s %s %s", op, arg1, arg2, result) == 4) {
        if (strcmp(op, "+") == 0) {
            fprintf(fp2, "\nMOV R0, %s", arg1);
            fprintf(fp2, "\nADD R0, %s", arg2);
            fprintf(fp2, "\nMOV %s, R0", result);
        } else if (strcmp(op, "*") == 0) {
            fprintf(fp2, "\nMOV R0, %s", arg1);
            fprintf(fp2, "\nMUL R0, %s", arg2);
            fprintf(fp2, "\nMOV %s, R0", result);
        } else if (strcmp(op, "-") == 0) {
            fprintf(fp2, "\nMOV R0, %s", arg1);
            fprintf(fp2, "\nSUB R0, %s", arg2);
            fprintf(fp2, "\nMOV %s, R0", result);
        } else if (strcmp(op, "/") == 0) {
            fprintf(fp2, "\nMOV R0, %s", arg1);
            fprintf(fp2, "\nDIV R0, %s", arg2);
            fprintf(fp2, "\nMOV %s, R0", result);
        } else if (strcmp(op, "=") == 0) {
            fprintf(fp2, "\nMOV R0, %s", arg1);
            fprintf(fp2, "\nMOV %s, R0", result);
        }
    }
    fprintf(fp2, "\n");

    fclose(fp1);
    fclose(fp2);

    printf("\nOutput written to output.txt\n");
    return 0;
}
