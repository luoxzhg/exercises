#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../mylib/mylib.h"

#define  BUFSIZE  4096
#define  SLEN    81

void append(FILE *dest, FILE *src);

int main(void)
{
    printf("Hello world!\n");
    FILE *fa, *fs;   // fa for appended file, fs for source file
    int files = 0;   // number of files appended
    char file_app[SLEN];  // name for appended file
    char file_src[SLEN];  // name for src file
    int ch;

    puts("Enter the name of destination file:");
    s_gets(file_app, SLEN);
    if (NULL == (fa = fopen(file_app, "a+b"))) {
        fprintf(stderr, "Can not open file: %s\n", file_app);
        exit(EXIT_FAILURE);
    }
    if (0 != setvbuf(fa, NULL, _IOFBF, BUFSIZE)) {
        fputs("Can not create buffer.\n", stderr);
        exit(EXIT_FAILURE);
    }

    puts("Enter name of first source file (empty line to quit):");
    while (NULL != s_gets(file_src, SLEN) && file_src[0] != '\0') {
        if (strcmp(file_src, file_app) == 0) {
            fputs("Can not append file to iteself\n", stderr);
            goto NEXT;
        }
        if ((fs = fopen(file_src, "r")) == NULL) {
            fprintf(stderr, "Can not open file: %s\n", file_src);
            goto NEXT;
        }
        if (0 != setvbuf(fs, NULL, _IOFBF, BUFSIZE)) {
            fputs("Can not create buffer.\n", stderr);
            exit(EXIT_FAILURE);
        }
        append(fa, fs);
        fclose(fs);
        ++files;
        fprintf(stdout, "File %s has been appended.\n", file_src);
    NEXT:
        puts("Next file (empty line to quit):");
    }

    printf("Done appending. %d files appended.\n", files);
    rewind(fa);
    printf("%s contents:\n", file_app);
    while (EOF != (ch = getc(fa)))
        putchar(ch);
    puts("Done displaying.");
    fclose(fa);
    return 0;
}


void append(FILE *dest, FILE *src)
{
    size_t  bytes;
    static char    temp[BUFSIZE];
    while ((bytes = fread(temp, sizeof(char), BUFSIZE, src)) > 0)
        fwrite(temp, sizeof(char), bytes, dest);
}
