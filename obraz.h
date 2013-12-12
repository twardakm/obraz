#ifndef OBRAZ_H
#define OBRAZ_H

typedef struct obraz
{
    char *nazwa_pliku;
    int rodzaj; //P1, P2....
    int czy_zmieniane;
    int width;
    int height;
    int color; //maksymalna wartość składowa koloru
    int **dane;
} obraz;

void inwersja(obraz *img);
void kafelki(obraz *img);
void obrot_180(obraz *img);
void obort_lewo(obraz *img);
void obrot_prawo(obraz *img);
void przyciemnij(obraz *img);
void rozjasnij(obraz *img);
void wyswietl_obraz(obraz *img);
int zarezerwuj_pamiec_dane(obraz *img);
void zmniejsz_obraz(obraz *img);
int zwolnij_pamiec_obraz(obraz *img);

#endif // OBRAZ_H
