#include "plik.h"
#include "errors.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int czy_zapisac()
{
    char ch;
    ch = getchar();

    if (ch == 'T' || ch == 't' || ch == 'Y' || ch == 'y')
        return 1;
    else if (ch == 'N' || ch == 'n')
        return 0;
    else
        czy_zapisac();
}

int odczytaj_dane(FILE *plik, obraz *img)
{
    int wiersz, kolumna, err, i;
    char c;

    if ((err = sprawdz_czy_komentarz(plik)) != COMMENT_OK)
    {
        if(_DEBUG) printf("Komentarz err: %d\n", err);
        return err;
    }

    //teraz dwie pętle do odczytu dwuwymiarowej tablicy
    for (wiersz = 0, i=0; wiersz < img->height; wiersz++, i++)
    {
        for(kolumna = 0; kolumna < img->width; kolumna++, i++)
            fscanf(plik, "%d", &img->dane[wiersz][kolumna]);

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
    if (_DEBUG) printf("Tyle razy odczytywano: %d\n", i);
    printf("Odczytywanie obrazu... OK");
    return READ_DATA_OK;
}

int odczytaj_maksymalny_kolor(FILE *plik, obraz *img)
{
    int err;
    if ((err = sprawdz_czy_komentarz(plik)) != COMMENT_OK)
    {
        if(_DEBUG) printf("Komentarz err: %d\n", err);
        return err;
    }
    fscanf(plik, "%d", &img->color);
    if (img->color <= 0)
    {
        printf("Błędny nagłówek pliku!\n");
        if (_DEBUG) printf("Odczytano: %d, err: %d\n", img->color, COLOR_ERR);
        return COLOR_ERR;
    }
    return COLOR_OK;
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
    if(temp->img->rodzaj == 2)
        if((err = odczytaj_maksymalny_kolor(plik, temp->img)) != COLOR_OK)
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
    temp->img->czy_zmieniane = 1;

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
    printf("Pliki pgm w tym folderze:\n");
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

int zapisz_plik(obraz *img)
{
    FILE *plik;
    int width, height;
    int n;

    printf("Czy chcesz nadpisać istniejący plik? (\'T\', \'N\') ");
    if(!czy_zapisac())
    {
        wyswietl_pliki();
        printf("Podaj nazwę nowego pliku: ");

        //konieczne żeby odczytywać całą linię
        //---------
        while(getchar() != '\n');
        fgets(img->nazwa_pliku, MAX_FILE_NAME, stdin);
        strtok(img->nazwa_pliku, "\n");
        //---------

        if (_DEBUG) printf("Odczytano: %s\n", img->nazwa_pliku);
    }

    if ((plik = fopen(img->nazwa_pliku, "w")) == NULL)
    {
        perror("Nie udało się otworzyć podanego pliku\n");
        return FILE_OPEN_ERR;
    }

    printf("Zapisywanie do pliku... ");

    fprintf(plik, "P%d\n%d %d\n", img->rodzaj, img->width, img->height);
    if(img->rodzaj == 2)
        fprintf (plik, "%d\n", img->color);

    for (height = 0, n=1; height < img->height; height++)
    {
        for (width = 0; width < img->width; width++, n++)
        {
            fprintf(plik, "%d ", img->dane[height][width]);
            if (n % 10 == 0)
            {
                fprintf(plik, "\n");
                n = 1;
            }
        }
        n = 1;
        fprintf(plik, "\n");
    }
    printf("OK\n");

    return SAVE_OK;
}
