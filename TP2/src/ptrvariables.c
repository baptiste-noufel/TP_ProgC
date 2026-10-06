#include <stdio.h>

static void afficher_octets(const void *adresse, size_t taille)
{
    const unsigned char *octets = adresse;

    for (size_t i = taille; i > 0; --i) {
        printf("%02x", octets[i - 1]);
    }
}

static void afficher_variables(const char *titre, const char *pc,
                               const short *ps, const int *pi, const long *pl,
                               const long long *pll, const float *pf,
                               const double *pd, const long double *pld)
{
    printf("%s\n", titre);
    printf("char       (%p) : ", (const void *)pc); afficher_octets(pc, sizeof *pc); putchar('\n');
    printf("short      (%p) : ", (const void *)ps); afficher_octets(ps, sizeof *ps); putchar('\n');
    printf("int        (%p) : ", (const void *)pi); afficher_octets(pi, sizeof *pi); putchar('\n');
    printf("long       (%p) : ", (const void *)pl); afficher_octets(pl, sizeof *pl); putchar('\n');
    printf("long long  (%p) : ", (const void *)pll); afficher_octets(pll, sizeof *pll); putchar('\n');
    printf("float      (%p) : ", (const void *)pf); afficher_octets(pf, sizeof *pf); putchar('\n');
    printf("double     (%p) : ", (const void *)pd); afficher_octets(pd, sizeof *pd); putchar('\n');
    printf("long double(%p) : ", (const void *)pld); afficher_octets(pld, sizeof *pld); putchar('\n');
}

int main(void)
{
    char c = 'A';
    short s = 10;
    int i = 20;
    long l = 30;
    long long ll = 40;
    float f = 1.0f;
    double d = 2.0;
    long double ld = 3.0L;

    char *pc = &c;
    short *ps = &s;
    int *pi = &i;
    long *pl = &l;
    long long *pll = &ll;
    float *pf = &f;
    double *pd = &d;
    long double *pld = &ld;

    afficher_variables("Avant la manipulation :", pc, ps, pi, pl, pll, pf, pd, pld);

    *pc = 'B';
    *ps += 1;
    *pi += 1;
    *pl += 1;
    *pll += 1;
    *pf += 1.0f;
    *pd += 1.0;
    *pld += 1.0L;

    afficher_variables("\nApres la manipulation :", pc, ps, pi, pl, pll, pf, pd, pld);
    return 0;
}