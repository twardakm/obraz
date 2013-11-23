#include "plik.h"
#include <stdlib.h>
#include <stdio.h>

int odczytaj_plik(element *lista)
{
    char *nazwa_pliku = (char *)malloc(sizeof(char) * MAX_FILE_NAME);
    FILE *plik;
    printf("Podaj nazwę pliku (maksymalnie %d znaków:)\n", MAX_FILE_NAME);
    scanf("%s", nazwa_pliku);
    if (_DEBUG) printf ("Nazwa pliku: %s\n", nazwa_pliku);

    printf("Otwieranie pliku... %s ", nazwa_pliku);
    //otwarcie podanego pliku w trybie do odczytu
    if((plik = fopen(nazwa_pliku, "r")) == NULL)
    {
        perror("Nie udało się otworzyć podanego pliku\n");
        return 1;
    }
    else
        printf("OK\n");

    //zapisywanie elemntu do listy
    element * temp = (element * )malloc(siezeof(element));
    temp->next = NULL;
    temp->img = (obraz *)malloc(sizeof(obraz));
    strcpy(temp->img->nazwa_pliku, nazwa_pliku);

    fclose(plik);
}
