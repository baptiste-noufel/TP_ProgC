#include <stdint.h>
#include <stdio.h>

#define TAILLE 100

struct couleur {
    uint8_t rouge;
    uint8_t vert;
    uint8_t bleu;
    uint8_t alpha;
};

static int egales(struct couleur a, struct couleur b)
{
    return a.rouge == b.rouge && a.vert == b.vert &&
           a.bleu == b.bleu && a.alpha == b.alpha;
}

int main(void)
{
    const struct couleur motifs[] = {
        {0xff, 0x23, 0x23, 0x45},
        {0xff, 0x00, 0x23, 0x12},
        {0x10, 0x20, 0x30, 0xff},
        {0x80, 0x80, 0x80, 0xff}
    };
    struct couleur couleurs[TAILLE];
    struct couleur distinctes[TAILLE];
    unsigned int occurrences[TAILLE] = {0};
    size_t nombre_distinctes = 0;

    for (size_t i = 0; i < TAILLE; ++i) {
        couleurs[i] = motifs[i % (sizeof motifs / sizeof motifs[0])];
    }

    for (size_t i = 0; i < TAILLE; ++i) {
        size_t j = 0;
        while (j < nombre_distinctes && !egales(couleurs[i], distinctes[j])) {
            ++j;
        }
        if (j == nombre_distinctes) {
            distinctes[nombre_distinctes] = couleurs[i];
            occurrences[nombre_distinctes] = 1;
            ++nombre_distinctes;
        } else {
            ++occurrences[j];
        }
    }

    for (size_t i = 0; i < nombre_distinctes; ++i) {
        printf("%02x %02x %02x %02x : %u\n",
               distinctes[i].rouge, distinctes[i].vert,
               distinctes[i].bleu, distinctes[i].alpha, occurrences[i]);
    }
    return 0;
}