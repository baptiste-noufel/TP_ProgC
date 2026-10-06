#include <stdio.h>

static unsigned long long factorielle(unsigned int n)
{
    if (n == 0) {
        return 1;
    }
    return n * factorielle(n - 1);
}

int main(void)
{
    unsigned int n;

    printf("Entrez un entier naturel (0 a 20) : ");
    if (scanf("%u", &n) != 1 || n > 20) {
        fprintf(stderr, "Valeur invalide.\n");
        return 1;
    }
    printf("%u! = %llu\n", n, factorielle(n));
    return 0;
}