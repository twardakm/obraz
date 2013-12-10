#ifndef MENU_H
#define MENU_H

#include "lista.h"
#include "obraz.h"

void tekst_powitalny(int ile);
void ustaw_kodowanie();
element * wiadomosc_powitalna(element *lista);
obraz * wybierz_obraz(element *lista);
int zakoncz_program(element *lista);

#endif // MENU_H
