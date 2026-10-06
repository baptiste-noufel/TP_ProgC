#include <stdio.h>

int main(void)
{
    const unsigned int n = 7;
    unsigned long long precedent = 0;
    unsigned long long courant = 1;

    for (unsigned int i = 0; i <= n; ++i) {
        printf("%llu", precedent);
        if (i < n) {
            printf(", ");
        }

        unsigned long long suivant = precedent + courant;
        precedent = courant;
        courant = suivant;
    }
    putchar('\n');

    return 0;
}