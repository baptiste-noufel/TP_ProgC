#include <stdio.h>

int main(void) {
    /* Types entiers : versions signées et non signées */
    printf("Taille de signed char : %zu octet(s)\n", sizeof(signed char));
    printf("Taille de unsigned char : %zu octet(s)\n", sizeof(unsigned char));

    printf("Taille de signed short : %zu octet(s)\n", sizeof(signed short));
    printf("Taille de unsigned short : %zu octet(s)\n", sizeof(unsigned short));

    printf("Taille de signed int : %zu octet(s)\n", sizeof(signed int));
    printf("Taille de unsigned int : %zu octet(s)\n", sizeof(unsigned int));

    printf("Taille de signed long int : %zu octet(s)\n", sizeof(signed long int));
    printf("Taille de unsigned long int : %zu octet(s)\n", sizeof(unsigned long int));

    printf("Taille de signed long long int : %zu octet(s)\n", sizeof(signed long long int));
    printf("Taille de unsigned long long int : %zu octet(s)\n", sizeof(unsigned long long int));

    /* Types flottants : pas de versions signed / unsigned */
    printf("Taille de float : %zu octet(s)\n", sizeof(float));
    printf("Taille de double : %zu octet(s)\n", sizeof(double));
    printf("Taille de long double : %zu octet(s)\n", sizeof(long double));

    return 0;
}
