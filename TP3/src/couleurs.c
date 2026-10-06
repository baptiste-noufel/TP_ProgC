#include <stdio.h>

int main(void)
{
    const char *couleurs[] = {"rouge", "vert", "bleu", "jaune", "violet"};

    for (size_t i = 0; i < sizeof couleurs / sizeof couleurs[0]; ++i) {
        printf("Couleur %zu : %s\n", i + 1, couleurs[i]);
    }
    return 0;
}