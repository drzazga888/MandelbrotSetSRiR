#pragma once

/**
 * Zawiera konfiguracje programu (wspolna dla workerow i managera)
 */
class Config{
	
	public:
		
		/**
		 * Statyczna metoda, ktora zwraca instancje klasy (model singleton)
		 */
		static Config& getInstance();
		
		/**
		 * Inicjalizacja programu
		 * @param argc - ilosc parametrow wejsciowych programu
		 * @param argv - tablica z parametrami wejsciowymi programu
		 */
		void initialize(int argc, char *argv[]);
		
		/**
		 * Zwraca ilosc wszystkich taskow / procesow, ktore
		 * sa uzywane jako workerzy
		 */
		int getNumOfClients();
		
		/**
		 * Minimalna wartosc Re(z) plaszczyzny
		 */
		double minx;
		
		/**
		 * Maksymalna wartosc Re(z) plaszczyzny
		 */
		double maxx;
		
		/**
		 * Minimalna wartosc Im(z) plaszczyzny
		 */
		double miny;
		
		/**
		 * Minimalna wartosc Im(z) plaszczyzny
		 */
		double maxy;
		
		/**
		 * Krok dyskretyzacji plaszczyzny
		 */
		double step;
		
		/**
		 * Wskazuje wartosc rank (tzn ID danego procesu w ramach MPI)
		 */
		int procRank;
		
	private:
		Config();
		void inputError(const char *message, const char *program);
		int procCount;
};
Config& appConfig();

