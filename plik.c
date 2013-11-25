#include "plik.h"
#include "errors.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int odczytaj_dane(FILE *plik, obraz *img)
{
    int wiersz, kolumna, err;
    char c;

    if ((err = sprawdz_czy_komentarz(plik)) != COMMENT_OK)
    {
        if(_DEBUG) printf("Komentarz err: %d\n", err);
        return err;
    }

    //teraz dwie pętle do odczytu dwuwymiarowej tablicy
    for (wiersz = 0; wiersz < img->height; wiersz++)
    {
        for(kolumna = 0; kolumna < img->width; kolumna++)
            fscanf(plik, "%d", &img->dane[wiersz][kolumna]);

        /*WAŻNE, musi odczytywać znak końca poprzedniej linii*/
        c = fgetc(plik);
        while(c != '\n' && c != EOF)
            c = fgetc(plik);
        /*----------*/
        // po każdej linii sprawdzenie czy komentarz
        if (c != EOF)
        {
            if ((err = sprawdz_czy_komentarz(plik)) != COMMENT_OK)
            {
                if(_DEBUG) printf("Komentarz err: %d\n", err);
                return err;
            }
        }
    }
    if (_DEBUG) //wyświetlenie tego co odczytane
    {
        for (wiersz = 0; wiersz < img->height; wiersz++)
        {
            for (kolumna = 0; kolumna < img->width; kolumna++)
                printf("%d ", img->dane[wiersz][kolumna]);
            printf("\n");
        }
    }
    printf("Odczytywanie obrazu... OK");
    return READ_DATA_OK;
}

element * odczytaj_plik(element *lista)
{
    char *nazwa_pliku = (char *)malloc(sizeof(char) * MAX_FILE_NAME + 1);
    FILE *plik;
    wyswietl_pliki(); //wyświetlanie dostępnych plików
    printf("Podaj nazwę pliku (maksymalnie %d znaków):\n", MAX_FILE_NAME);
    //konieczne żeby odczytywać całą linię
    //---------
    while(getchar() != '\n');
    fgets(nazwa_pliku, MAX_FILE_NAME, stdin);
    strtok(nazwa_pliku, "\n");
    //---------

    if (_DEBUG) printf ("Nazwa pliku: %s\n", nazwa_pliku);

    printf("Otwieranie pliku... %s ", nazwa_pliku);
    //otwarcie podanego pliku w trybie do odczytu
    if((plik = fopen(nazwa_pliku, "r")) == NULL)
    {
        perror("Nie udało się otworzyć podanego pliku\n");
        return lista;
    }
    else
        printf("OK\n");

    //zapisywanie elemntu do listy
    int err;
    element * temp = (element * )malloc(sizeof(element));
    temp->next = NULL;
    temp->img = (obraz *)malloc(sizeof(obraz));
    temp->img->nazwa_pliku = (char *)malloc(sizeof(char) * strlen(nazwa_pliku));
    strcpy(temp->img->nazwa_pliku, nazwa_pliku);

    if((err = odczytaj_rodzaj_obrazka(plik, temp->img)) != ART_OK)
    {
        printf("Błąd odczytu z pliku\n");
        fclose(plik);
        free(nazwa_pliku);
        if(_DEBUG) printf("Błąd %d\n", err);
        return lista;
    }
    if((err = odczytaj_wielkosc_obrazka(plik, temp->img)) != SIZE_OK)
    {
        printf("Błąd odczytu z pliku\n");
        fclose(plik);
        free(nazwa_pliku);
        if(_DEBUG) printf("Błąd %d\n", err);
        return lista;
    }
    if((err = zarezerwuj_pamiec_dane(temp->img)) != MALLOC_OK)
    {
        printf("Błąd odczytu z pliku!\n");
        fclose(plik);
        free(nazwa_pliku);
        if(_DEBUG) printf("Błąd %d\n", err);
        return lista;
    }
    if((err = odczytaj_dane(plik, temp->img)) != READ_DATA_OK)
    {
        printf("Błąd odczytu z pliku!\n");
        fclose(plik);
        free(nazwa_pliku);
        if(_DEBUG) printf("Błąd %d\n", err);
        return lista;
    }

    lista = push(lista,temp);

    fclose(plik);
    free(nazwa_pliku);

    return lista;
}

int odczytaj_rodzaj_obrazka(FILE *plik, obraz *img)
{
    int err;
    if ((err = sprawdz_czy_komentarz(plik)) != COMMENT_OK)
    {
        if(_DEBUG) printf("Komentarz err: %d\n", err);
        return err;
    }
    char c;
    //odczytanie litery 'P'
    c = fgetc(plik);
    if (c != 'P')
    {
        printf("Błędny nagłówek pliku!\n");
        if (_DEBUG) printf("(1) Odczytano: %c, err: %d\n", c, ART_FIRST);
        return ART_FIRST;
    }
    if (_DEBUG) printf("(1) Odczytano: %c\n", c);
    //odczytanie rodzaju
    fscanf(plik, "%d", &img->rodzaj);
    if (img->rodzaj < 0 || img->rodzaj > 6)
    {
        printf("Błędny nagłówek pliku!\n");
        if (_DEBUG) printf("(2) Odczytano: %d, err: %d\n", img->rodzaj, ART_NUMBER);
        return ART_NUMBER;
    }
    if (_DEBUG) printf("(2) Odczytano: %d\n", img->rodzaj);

    while(fgetc(plik) != '\n') {} // konieczne, bo inaczej wywala śmieci
    return ART_OK;
}

int odczytaj_wielkosc_obrazka(FILE *plik, obraz *img)
{
    int err;
    if ((err = sprawdz_czy_komentarz(plik)) != COMMENT_OK)
    {
        if(_DEBUG) printf("Komentarz err: %d\n", err);
        return err;
    }
    fscanf(plik,"%d",&img->width);
    if(img->width <= 0)
    {
        printf("Błędny nagłówek pliku!\n");
        if (_DEBUG) printf("(3) Odczytano: %d, err: %d\n", img->width, SIZE_WIDTH);
        return SIZE_WIDTH;
    }
    if (_DEBUG) printf("(3) Odczytano: %d\n", img->width);
    fscanf(plik, "%d", &img->height);
    if(img->width <= 0)
    {
        printf("Błędny nagłówek pliku!\n");
        if (_DEBUG) printf("(4) Odczytano: %d, err: %d\n", img->height, SIZE_HEIGHT);
        return SIZE_HEIGHT;
    }
    if (_DEBUG) printf("(4) Odczytano: %d\n", img->height);
    while(fgetc(plik) != '\n') {}
    return SIZE_OK;
}

int sprawdz_czy_komentarz(FILE *plik)
{
    char c = fgetc(plik);
    while (c == '#' && c != EOF)
    {
        if (_DEBUG) printf("Znaleziono komentarz\n");
        do
        {
            c = fgetc(plik);
        } while (c != '\n' && c != EOF);
        c = fgetc(plik);
    }
    if (!fseek(plik, ftell(plik) - 1, SEEK_SET))
    {
        if (_DEBUG) printf("Nie znaleziono komentarza\n");
        return COMMENT_OK;
    }
    else
    {
        printf("Błąd odczytu z pliku\n");
        return COMMENT_ERR;
    }
}

int wyswietl_pliki()
{
#ifdef WIN32
    FILE *ls = _popen("dir /b *.pgm", "r");
#else
    FILE *ls = popen("ls *.pgm", "r");
#endif
    if (ls == NULL)
    {
        perror ("Nie odnaleziono polecenia ls, wpisz nazwę pliku z pamięci\n");
        return LS_NOT_FOUND;
    }
    char * temp = (char *)malloc(sizeof(char) * MAX_FILE_NAME + 1);
    temp[0] = '\0';
    printf("Pliki do wyboru w tym folderze:\n");
    do
    {
        printf("%s", temp);
        fgets(temp, MAX_FILE_NAME, ls);
    } while(!feof(ls));
    free(temp);
#ifdef WIN32
    _pclose(ls);
#else
    pclose(ls);
#endif
}
