mandelbrot.run: main.cpp Board.o Client.o Server.o Config.o Utils.o
	mpicxx main.cpp Board.o Client.o Server.o Config.o Utils.o -o mandelbrot.run -lmpe

Board.o: Board.cpp
	mpicxx -c Board.cpp -o Board.o
	
Client.o: Client.cpp
	mpicxx -c Client.cpp -o Client.o
	
Server.o: Server.cpp
	mpicxx -c Server.cpp -o Server.o
	
Config.o: Config.cpp
	mpicxx -c Config.cpp -o Config.o
	
Utils.o: Utils.cpp
	mpicxx -c Utils.cpp -o Utils.o

.PHONY: clean
 
clean:
	rm -f *.o mandelbrot.run