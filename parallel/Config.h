#pragma once

class Config{
	public:
		static Config& getInstance();
		void initialize(int argc, char *argv[]);	
		int getNumOfClients();
		
		double minx;
		double maxx;
		double miny;
		double maxy;
		double step;
		int procRank;
	private:
		Config();
		void inputError(const char *message, const char *program);
		int procCount;
};
Config& appConfig();

