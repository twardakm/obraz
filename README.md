obraz
=====

Program do obsługi obrazów pgm w języku C

Zawiera cmake, aby skompilować i uruchomić należy w katalogu wywołać:
1. cmake ./
2. make
3. ./generowanie_obrazu

Istnieje możliwość kompilacji w trybie debugowania, wtedy w pliku CMakeList.txt należy zmienić flagę -D_DEBUG=0 na -D_DEBUG=1

DZIAŁANIE PROGRAMU

Na początku należy wczytać obrazy na których się chce pracować. Można to zrobić za pomocą opcji 11 i wtedy pojedynczo wpisywać nazwy, bądź opcji 12 wtedy wczytane zostaną do pamięci wszystkie obrazy z rozszerzeniem *.pgm znajdujące się w folderze pliku uruchomieniowego.

Po wczytaniu obrazu można wybrać jedną z funkcji:
1. FILTRY
  a) Inwersja -> odwraca kolory
  b) Rozjaśnienie -> po podaniu wartości w % rozjaśnia wskazany obraz
  c) Przyciemnienie -> po podaniu wartości w % przyciemnia wskazany obraz
  d) Kafelki -> po podaniu promienia kafaleka tworzy efekt kafelkowy
  e) Rozmycie -> po podaniu promienia rozmycia rozmywa obraz
2. EDYCJA OBRAZU
  a) Obroty (w prawo, lewo, o 180) obraca wskazany obraz
  b) Zmniejsz obraz -> po podaniu nowych wymiarów można wybrać z której strony zostanie przycięty wskazany obraz
  c) Zmień rozmiar -> można dowolnie zmieniać wymiary (wtedy obraz zostaje rozciągnięty). Maksymalny wymiar to 3000 x 3000
3. Zapisz zmienione obrazy -> wykrywa które obrazy zostały w danej sesji zmienione i pozwala na ich zapis (do wyboru nadpisanie bądź stworzenie nowego pliku)
4. Przy wychodzeniu program zapyta, czy zapisać zmienione pliki

Marcin Twardak
