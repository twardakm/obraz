#ifndef OBRAZ_H
#define OBRAZ_H

typedef struct obraz
{
    char *nazwa_pliku;
    int rodzaj; //P1, P2....
    int width;
    int height;
    int **dane;
} obraz;

#endif // OBRAZ_H
