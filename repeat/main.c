#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("Hello world!\n");
    printf("The command line has %d arguments: \n", argc - 1);
    for (int count = 1; count < argc; ++count)
        printf("%d: %s\n", count, argv[count]);
    putchar('\n');

    return 0;
}
