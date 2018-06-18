#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 81
#define CTRL_Z '\032'  // end marker in DOS text file

int main(void)
{
    printf("Hello world!\n");
    puts("Enter the name of the file to be processed:");
    char name[SIZE];
    fgets(name, SIZE, stdin);
    char *p = strchr(name, '\n');
    if (p != NULL)
        *p = '\0';

    FILE *pf = fopen(name, "r+b");
    if (pf == NULL) {
        fprintf(stderr, "can not open the file: %s.\n", name);
        exit(EXIT_FAILURE);
    }

    fseek(pf, 0, SEEK_END);
    long  count = ftell(pf);
    for (long i = 1; i <= count; ++i) {
        fseek(pf, -i, SEEK_END);
        int ch = getc(pf);
        if (ch != CTRL_Z && ch != '\r')
            putchar(ch);
    }
    putchar('\n');
    if (fclose(pf) != 0) {
        fprintf(stderr, "can not close file: %s", name);
        exit(EXIT_FAILURE);
    }

    return 0;
}
