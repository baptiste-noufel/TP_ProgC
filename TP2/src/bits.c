#include <stdint.h>
#include <stdio.h>

int main(void)
{
    /*
     * Les bits sont numérotés depuis la gauche, de 1 à 32.
     * Les 4e et 20e bits correspondent donc aux positions 28 et 12
     * depuis la droite dans une valeur sur 32 bits.
     */
    const uint32_t d = UINT32_C(0x10001000);
    const uint32_t bit4 = (d >> 28) & UINT32_C(1);
    const uint32_t bit20 = (d >> 12) & UINT32_C(1);

    printf("%u\n", bit4 & bit20);
    return 0;
}