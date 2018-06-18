// Checks numbers for repeated digits
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

int main(void)
{
    printf("Hello world!\n");
    bool  digit_seen[10] = {false};
    int ch, digit;
    printf("Enter a number: ");
    while ('\n' != (ch = getchar()))
    {
        if (!isdigit(ch))
            exit(EXIT_FAILURE);
        digit = ch - '0';
        if (digit_seen[digit])
        {
            printf("Repeated digit\n");
            return 0;
        }
        digit_seen[digit] = true;
    }
    printf("No Repeated digit\n");
    return 0;
}
