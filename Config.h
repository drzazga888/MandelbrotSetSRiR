#pragma once

class Config{
	public:
		static Config& getInstance();
		void initialize(int argc, char *argv[]);	
		
		double minx;
		double maxx;
		double miny;
		double maxy;
		double step;
	private:
		Config();
		void inputError(const char *message, const char *program);
};
Config& appConfig();

