MPICXXFLAGS =
DEFINES =

all: mandelbrot.run

mpelogs: MPICXXFLAGS += -lmpe
mpelogs: DEFINES += -D MPE_LOGS
mpelogs: mandelbrot.run

mandelbrot.run: main.cpp Board.o Client.o Server.o Config.o Utils.o
	mpicxx main.cpp Board.o Client.o Server.o Config.o Utils.o -o mandelbrot.run $(MPICXXFLAGS) $(DEFINES)

Board.o: Board.cpp
	mpicxx -c Board.cpp -o Board.o $(DEFINES)
	
Client.o: Client.cpp
	mpicxx -c Client.cpp -o Client.o $(DEFINES)
	
Server.o: Server.cpp
	mpicxx -c Server.cpp -o Server.o $(DEFINES)
	
Config.o: Config.cpp
	mpicxx -c Config.cpp -o Config.o $(DEFINES)
	
Utils.o: Utils.cpp
	mpicxx -c Utils.cpp -o Utils.o $(DEFINES)

.PHONY: clean
clean:
	rm -f *.o mandelbrot.run data.txt result.png *.clog2 *.slog2