#pragma once
#include <string>

/**
* Wyswietla komunikat bledu i konczy dzialanie programu
* @param message komunikat bledu
*/
void error(const char *message);

/**
* Wyswietla ostrzezenie
* @param message wiadomosc do wyswietlenia
*/
void warning(std::string message);

/**
* Oblicza liczbe wierszy, jaka ma byc w utworzonej planszy
* @param miny minimalna wartosc y (czyli Im(z)) na plaszczyznie
* @param miny maksymalna wartosc y (czyli Im(z)) na plaszczyznie
* @param step krok dyskretyzacji
* @return docelowa ilosc wierszy
*/
int getRows(double miny, double maxy, double step);

/**
* Oblicza liczbe kolumn, jaka ma byc w utworzonej planszy
* @param miny minimalna wartosc x (czyli Re(z)) na plaszczyznie
* @param miny maksymalna wartosc x (czyli Re(z)) na plaszczyznie
* @param step krok dyskretyzacji
* @return docelowa ilosc kolumn
*/
int getCols(double minx, double maxx, double step);

/**
* Zwalnia pamiec, na ktorej zapisana jest plaszczyzna
* @param board zdyskretyzowana plaszczyzna
* @param rows ilosc wierszy plaszczyzny
*/
void freeBoard(int **board, int rows);

/**
* Inicjuje plaszczyzne
* @param rows ilosc wierszy
* @param cols ilosc kolumn
*/
int **initBoard(int rows, int cols);

/**
* Wyswietla informacje o rozpoczeciu pomiaru czasu dzialania
* fragmentu kodu (do debugowania)
* @param startTime poczatkowy czas w ms
* @param message wiadomosc do wyswietlenia
*/
void debugTimeStart(double startTime, std::string message = "");

/**
* Wyswietla informacje konczace pomiaru czasu dzialania
* fragmentu kodu (do debugowania)
* @param startTime poczatkowy czas w ms
* @param message wiadomosc do wyswietlenia
*/
void debugTimeEnd(double startTime, std::string message = "");
