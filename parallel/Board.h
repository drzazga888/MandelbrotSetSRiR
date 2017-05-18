#pragma once

/**
 * Klasa, ktora reprezentuje cala nasza plaszczyzne zespolona
 */
class Board{
	
	public:
		
		/**
		 * Konstruktor - alokuje pamiec
		 */
		Board();
		
		/**
		 * Destruktor - czysci pamiec
		 */
		~Board();
		
		/**
		 * Zwraca liczbe wierwszy na plaszczyznie
		 * @return liczba wierszy
		 */
		int getRows();
		
		/**
		 * Zwraca liczbe kolumn na plaszczyznie
		 * @return liczba kolumn
		 */
		int getCols();
		
		/**
		 * Zwraca nastepny numer wiersza, jaki trzeba bedzie obliczyc
		 * @returns numer wiersza
		 */
		int next();
		
		/**
		 * Pozwala ustawic caly wiersz danych na plaszczyznie
		 * @param row numer wiersza, do ktorego zostana wstawione dane
		 * @param data tablica danych o rozmiarze bedacym iloscia kolumn na plaszczyznie
		 */
		void setRow(int row, int *data);
		
		/**
		 * Sprawdza, czy jest cos jeszcze do liczenia, wspolpracuje z funkcja next()
		 * @return informacja, czy nalezy jeszcze wyonywac obliczenia
		 * @see next()
		 */
		bool areStillRowsToProcess();
		
		/**
		 * Pobiera caly wiersz danych
		 * @param row numer wiersza
		 * @return caly wskazany wiersz danych
		 */
		int* getRow(int row);
		
		/**
		 * Zwraca cala plaszczyzne danych
		 * @return plaszczyzna 2D
		 */
		int** getBoardData();

	private:
		
		int** board;
		int currentRow;
		int rows;
		int cols;
		void init();
		void free();
		
};
