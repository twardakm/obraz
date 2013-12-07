#include "menu.h"
#include "obraz.h"
#include "plik.h"
#include "lista.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>

void tekst_powitalny(int ile)
{
    printf("\nODCZYTYWANIE OBRAZU\n--------------------------------\n");
    printf("Obrazów w pamięci: %d\n", ile);
    printf("1 - Dodaj obraz\n"
           "2 - Wyswietl obraz\n"
           "31 - Inwersja\n"
           "0 - Wyjdź\n");
}

void ustaw_kodowanie()
{
#ifdef WIN32
    system("chcp 65001");
#endif
}

element * wiadomosc_powitalna(element *lista)
{
    tekst_powitalny(size(lista));
    int c;

    while(c = getchar())
    {
        switch(c)
        {
        case '1':
            if(_DEBUG) printf("Wybrano %c\n",c);
            lista = odczytaj_plik(lista);
            break;
        case '2':
            if (_DEBUG) printf("Wybrano %c\n", c);
            wyswietl_obraz(wybierz_obraz(lista));
            break;
        case '3':
            if (_DEBUG) printf("Wybrano %c", c);
            c = getchar();
            switch(c)
            {
            case '1': //inwersja
                if (_DEBUG) printf("%c\n", c);
                inwersja(wybierz_obraz(lista));
                break;
            default:
                printf("Niepoprawny wybór\n");
                break;
            }
            break;
        case '0':
            if(_DEBUG) printf("Wybrano %c\n",c);
            zakoncz_program(lista);
            printf("Dziękuję za skorzystanie z programu!\nMarcin Twardak\n");
            return lista;
        default:
            tekst_powitalny(size(lista));
            break;
        }
    }
}

obraz * wybierz_obraz(element *lista)
{
    int ile = size(lista);
    if (!ile)
    {
        printf("Nie wczytano dotąd żadnego obrazu!\n");
        return NULL;
    }
    int n;
    while(getchar() != '\n');
    printf("Wybierz, który obraz chcesz zmienić:\n"
           "Ilość wczytanych obrazów: %d\n", ile);
    wyswietl_wczytane_obrazy(lista);
    scanf("%d", &n);
    element * temp = position(lista, n - 1);
    if (temp == NULL)
        return NULL;

    return temp->img;
}

int zakoncz_program(element *lista)
{
    int i, err;
    int ile = size(lista);
    for (i = 0; i < ile; i++)
    {
        if (lista->img->czy_zmieniane)
        {
            printf("Plik %s został zmieniony\n"
                   "Czy chcesz go zapisać? (\'T\', \'N\') ",
                   lista->img->nazwa_pliku);
            if (czy_zapisac())
            {
                if((err = zapisz_plik(lista->img)) != SAVE_OK)
                {
                    printf("Nie udało się zapisać pliku %s\n", lista->img->nazwa_pliku);
                    if (_DEBUG) printf("Bład: %d\n", err);
                }
            }
        }
        lista = lista->next;
    }
    return END_OK;
}
