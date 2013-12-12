#include "obraz.h"
#include "lista.h"
#include "errors.h"
#include <stdlib.h>
#include <stdio.h>

void inwersja(obraz *img)
{
    if (img == NULL)
        return;
    int width, height;

    if (img->rodzaj == 1)
    {
        for(height = 0; height < img->height; height++)
        {
            for (width = 0; width < img->width; width++)
            {
                if (img->dane[height][width])
                    img->dane[height][width] = 0;
                else
                    img->dane[height][width] = 1;
            }
        }
    }
    else
    {
        for(height = 0; height < img->height; height++)
        {
            for (width = 0; width < img->width; width++)
                img->dane[height][width] = img->color - img->dane[height][width];
        }
    }

    img->czy_zmieniane = 1;
    return;
}

void kafelki(obraz *img)
{
    if (img == NULL)
        return;
    if (img->rodzaj == 1)
    {
        printf("Kafelki nie są obsługiwane dla tego typu pliku\n");
        return;
    }

    int r, i, j, k, l, suma, wsp, sr;

    printf("Podaj wielkość kafelka: ");
    scanf("%d", &r);

    for (i = r; i < (img->height - r); i+=(2*r + 1))
    {
        for (j = r; j < img->width - r; j += (2*r + 1))
        {
            suma = 0;
            for (k = (i - r); k < (i + r); k++)
            {
                for (l = (j - r); l < (j + r); l++)
                    suma += img->dane[k][l];
            }
            for (k = (i - r); k < (i + r); k++)
            {
                wsp = suma / ((2*r + 1) * (2*r+1));
                for (l = (j - r); l < (j + r); l++)
                    img->dane[k][l] = wsp;
            }
        }
        //warunki brzegowe
        wsp = 0;
        suma = 0;
        if ((j - r) < (img->width - 1))
        {
            for (k = (i - r); k < (i + r) && k < img->height; k++)
            {
                for (l = (j - r); l < img->width; l++)
                {
                    suma += img->dane[k][l];
                    wsp++;
                }
            }
            for (k = (i - r); k < (i + r) && k < img->height; k++)
            {
                for (l = (j - r); l < img->width; l++)
                {
                    sr = suma / wsp;
                    img->dane[k][l] = sr;
                }
            }
        }
    }
    wsp = 0;
    suma = 0;
    i -= r;
    if (i < img->height - 1)
    {
        for (j = r; j < img->width; j += (2*r + 1))
        {
            wsp = 0;
            suma = 0;
            for (k = i; k < img->height; k++)
            {
                for (l = (j - r); l < (j + r) && l < img->width; l++)
                {
                    suma += img->dane[k][l];
                    wsp++;
                }
            }
            sr = suma / wsp;
            for (k = i; k < img->height; k++)
            {
                for (l = (j - r); l < (j + r) && l < img->width; l++)
                {
                    img->dane[k][l] = sr;
                }
            }
        }
    }
    if (_DEBUG) printf("k: %d\tl: %d", k, l);

    img->czy_zmieniane = 1;

    return;
}

void obrot_180(obraz *img)
{
    if (img == NULL)
        return;
    int i,j,k,l;
    int **dane;
    if (_DEBUG) printf("Obrót o 180");

    dane = (int **)malloc(sizeof(int *) * img->height);
    for (i = 0; i < img->height; i++)
        dane[i] = (int *)malloc(sizeof(int) * img->width);
    if (_DEBUG) printf("Zaalokowano pamięć\n");

    for (i = 0, j = img->height - 1; i<img->height; i++, j--)
    {
        for (k = 0, l = img->width-1; k < img->width; k++,l--)
            dane[i][k] = img->dane[j][l];
    }

    if (_DEBUG) printf("zwalnianie pamięci\n");

    for(i = 0; i < img->height; i++)
        free(img->dane[i]);
    free(img->dane);

    img->dane = dane;

    img->czy_zmieniane = 1;
    return;
}

void obrot_lewo(obraz *img)
{
    if (img == NULL)
        return;
    int i, j, k;
    int **dane;
    if (_DEBUG) printf("Obrót w prawo\n");

    dane = (int **)malloc(sizeof(int *) * img->width);
    for (i = 0; i < img->width; i++)
        dane[i] = (int *)malloc(sizeof(int) * img->height);
    if (_DEBUG) printf("Zaalokowano pamięć\n");

    for (j = 0; j < img->width; j++)
    {
        for (i = img->height - 1, k = 0; i >= 0; i--, k++)
            dane[j][k] = img->dane[k][img->width-j-1];
    }
    if(_DEBUG) printf("zwalnianie pamięci\n");
    for(i = 0; i < img->height; i++)
        free(img->dane[i]);
    free(img->dane);

    img->dane = dane; //przypisanie adresu
    i = img->width;
    j = img->height;
    img->height = i;
    img->width = j;

    img->czy_zmieniane = 1;
    return;
}

void obrot_prawo(obraz *img)
{
    if (img == NULL)
        return;
    int i, j, k;
    int **dane;
    if (_DEBUG) printf("Obrót w prawo\n");

    dane = (int **)malloc(sizeof(int *) * img->width);
    for (i = 0; i < img->width; i++)
        dane[i] = (int *)malloc(sizeof(int) * img->height);
    if (_DEBUG) printf("Zaalokowano pamięć\n");

    for (j = 0; j < img->width; j++)
    {
        for (i = img->height - 1, k = 0; i >= 0; i--, k++)
            dane[j][k] = img->dane[i][j];
    }
    if(_DEBUG) printf("zwalnianie pamięci\n");
    for(i = 0; i < img->height; i++)
        free(img->dane[i]);
    free(img->dane);

    img->dane = dane; //przypisanie adresu
    i = img->width;
    j = img->height;
    img->height = i;
    img->width = j;

    img->czy_zmieniane = 1;
    return;
}

void przyciemnij(obraz *img)
{
    if (img == NULL)
        return;
    if (img->rodzaj == 1)
    {
        printf("Nie można przyciemnić tego typu pliku!\n");
        return;
    }

    int wsp, i ,j;

    do
    {
        printf("O ile procent przyciemnić: ");
        scanf("%d", &wsp);
    } while (wsp <= 0);
    double a = wsp / 100.;

    for (i = 0; i < img->height; i++)
    {
        for (j = 0; j < img->width; j++)
        {
            img->dane[i][j] -= img->dane[i][j] * a;
            if (img->dane[i][j] < 0)
                img->dane[i][j] = 0;
        }
    }

    img->czy_zmieniane = 1;
    return;
}

void rozjasnij(obraz *img)
{
    if (img == NULL)
        return;
    if (img->rodzaj == 1)
    {
        printf("Nie można rozjaśnić tego typu pliku!\n");
        return;
    }

    int wsp, i ,j;

    do
    {
        printf("O ile procent rozjaśnić: ");
        scanf("%d", &wsp);
    } while (wsp <= 0 || wsp > 100);
    wsp *= img->color;

    for (i = 0; i < img->height; i++)
    {
        for (j = 0; j < img->width; j++)
        {
            img->dane[i][j] += wsp;
            if (img->dane[i][j] > img->color)
                img->dane[i][j] = img->color;
        }
    }

    img->czy_zmieniane = 1;
    return;
}

void rozmycie_Gaussa(obraz *img)
{
    if (img == NULL)
        return;
    if (img->rodzaj == 1)
    {
        printf("Rozmycie Gaussa nie jest obsługiwane dla tego typu pliku\n");
        return;
    }

    int r, i, j, k, l, suma, wsp, sr;

    printf("Podaj promień rozmycia: ");
    scanf("%d", &r);

    for (i = r; i <= (img->height - r); i+=r/1.5)
    {
        for (j = r; j <= img->width - r; j+=r/1.5)
        {
            suma = 0;
            for (k = (i - r); k <= (i + r) && k < img->height; k++)
            {
                for (l = (j - r); l < (j + r); l++)
                    suma += img->dane[k][l];
            }
            for (k = (i - r); k <= (i + r) && k < img->height; k++)
            {
                wsp = suma / ((2*r + 1) * (2*r));
                for (l = (j - r); l < (j + r); l++)
                    img->dane[k][l] = wsp;
            }
        }
        //warunki brzegowe
        wsp = 0;
        suma = 0;
        if ((j - r) < (img->width - 1))
        {
            for (k = (i - r); k <= (i + r) && k < img->height; k++)
            {
                for (l = (j - r); l < img->width; l++)
                {
                    suma += img->dane[k][l];
                    wsp++;
                }
            }
            for (k = (i - r); k <= (i + r) && k < img->height; k++)
            {
                for (l = (j - r); l < img->width; l++)
                {
                    sr = suma / wsp;
                    img->dane[k][l] = sr;
                }
            }
        }
    }
    wsp = 0;
    suma = 0;
    i -= r;
    if (i < img->height - 1)
    {
        for (j = r; j < img->width; j+=r/1.5)
        {
            wsp = 0;
            suma = 0;
            for (k = i; k < img->height; k++)
            {
                for (l = (j - r); l <= (j + r) && l < img->width; l++)
                {
                    suma += img->dane[k][l];
                    wsp++;
                }
            }
            sr = suma / wsp;
            for (k = i; k < img->height; k++)
            {
                for (l = (j - r); l <= (j + r) && l < img->width; l++)
                {
                    img->dane[k][l] = sr;
                }
            }
        }
    }
    if (_DEBUG) printf("k: %d\tl: %d", k, l);

    img->czy_zmieniane = 1;

    return;
}

void wyswietl_obraz(obraz *img)
{
    if (img == NULL)
        return;
    printf("\n---------------\nWyswietlanie obrazu: %s\n---------------\n"
           "Rodzaj: P%d\tWysokość: %d\tSzerokość: %d\n"
           "Maksymalna wartość składowa koloru: %d\n---------------\n",
           img->nazwa_pliku, img->rodzaj, img->height, img->width, img->color);

    if (img->rodzaj == 1)
    {
        int wiersz, kolumna;

        for (wiersz = 0; wiersz < img->height; wiersz++)
        {
            for (kolumna = 0; kolumna < img->width; kolumna++)
            {
                if (img->dane[wiersz][kolumna] == 0)
                    printf("  ");
                else
                    printf("%c ", 35);
            }
            printf("\n");
        }
    }
}

int zarezerwuj_pamiec_dane(obraz *img)
{
    int i;
    if (_DEBUG) printf("width: %d\n", img->width);
    if (_DEBUG) printf("height: %d\n", img->height);
    img->dane = (int **)malloc(sizeof(int *) * img->height);
    if(_DEBUG) printf("Zaalokowano y = %d\n", img->height);
    for(i = 0; i < img->height; i++)
        img->dane[i] = (int *)malloc(sizeof(int) * img->width);
    if(_DEBUG) printf("Zaalokowano x = %d\n", img->width);
    return MALLOC_OK;
}

void zmniejsz_obraz(obraz *img)
{
    if(img == NULL)
        return;
    int c = 0;
    int width, height, i, j, k, l, **dane;
    printf("Aktualne wymiary:\n"
           "Szerokość:\t%d\n"
           "Wysokość:\t%d\n"
           "Podaj nowe rozmiary\n",
           img->width, img->height);
    do
    {
        printf("Szerokość: ");
        scanf("%d", &width);
    } while (width > img->width || width <= 0);
    do
    {
        printf("Wysokość: ");
        scanf("%d", &height);
    } while (height > img->height || height <= 0);

    dane = (int **)malloc(sizeof(int) * height);
    for(i = 0; i < height; i++)
        dane[i] = (int *)malloc(sizeof(int) * width);
    if(_DEBUG) printf("Zaalokowano pamięć\n");

    while (c != -1)
    {
        printf("Wybierz w jaki sposób zmniejszyć obraz:\n"
               "1 - Od lewego górnego rogu\n"
               "2 - Od lewego dolnego rogu\n"
               "3 - Od prawego górnego rogu\n"
               "4 - Od prawego dolnego rogu\n"
               "5 - Od środka\n"
               "0 - Wyjdź\n");

        while((c = getchar()) == '\n');
        switch(c)
        {
        case ('1'):
            if (_DEBUG) printf("Wybrano: %c\n", c);
            for (i = 0; i < height; i++)
                for (j = 0; j < width; j++)
                    dane[i][j] = img->dane[i][j];
            c = -1;
            break;
        case ('2'):
            if (_DEBUG) printf("Wybrano: %c\n", c);
            for (i = img->height - height, k = 0; i < img->height; i++, k++)
                for (j = 0; j < width; j++)
                    dane[k][j] = img->dane[i][j];
            c = -1;
            break;
        case ('3'):
            if (_DEBUG) printf("Wybrano: %c\n", c);
            for (i = 0; i < height; i++)
                for (j = (img->width - width), k = 0; j < img->width; j++, k++)
                    dane[i][k] = img->dane[i][j];
            c = -1;
            break;
        case ('4'):
            if (_DEBUG) printf("Wybrano: %c\n", c);
            for (i = img->height - height, k = 0; i < img->height; i++, k++)
                for (j = img->width - width, l = 0; j < img->width; j++, l++)
                    dane[k][l] = img->dane[i][j];
            c = -1;
            break;
        case ('5'):
            if (_DEBUG) printf("Wybrano: %c\n", c);
            for (i = (img->height/2 - height/2), k = 0; i < (img->height / 2 + height/2); i++, k++)
                for (j = (img->width/2 - width/2), l = 0; j < (img->width / 2 + width/2); j++, l++)
                    dane[k][l] = img->dane[i][j];
            c = -1;
            break;
        default:
            printf("Niepoprawny wybór\n");
            break;
        }
    }
    printf("Zmniejszanie obrazu... OK\n");
    for(i = 0; i < img->height; i++)
        free(img->dane[i]);
    free(img->dane);

    if(_DEBUG) printf("Zwolniono dane\n");

    img->dane = dane;

    img->width = width;
    img->height = height;
    img->czy_zmieniane = 1;
    return;
}

int zwolnij_pamiec_obraz(obraz *img)
{
    int i;
    if (_DEBUG) printf("zwalnianie pamieci... ");
    free(img->nazwa_pliku);

    for(i = 0; i < img->height; i++)
        free(img->dane[i]);
    free(img->dane);

    if (_DEBUG) printf("OK\n");

    return FREE_MEM_OK;
}
