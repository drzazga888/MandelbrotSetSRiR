CC = mpicxx
MPICXXFLAGS =
DEFINES =

all: mandelbrot.run

mpelogs: MPICXXFLAGS += -lmpe
mpelogs: DEFINES += -D MPE_LOGS
mpelogs: mandelbrot.run

mandelbrot.run: main.cpp Board.o Client.o Server.o Config.o Utils.o
	$(CC) main.cpp Board.o Client.o Server.o Config.o Utils.o -o mandelbrot.run $(MPICXXFLAGS) $(DEFINES)

Board.o: Board.cpp
	$(CC)  -c Board.cpp -o Board.o $(DEFINES)
	
Client.o: Client.cpp
	$(CC)  -c Client.cpp -o Client.o $(DEFINES)
	
Server.o: Server.cpp
	$(CC)  -c Server.cpp -o Server.o $(DEFINES)
	
Config.o: Config.cpp
	$(CC)  -c Config.cpp -o Config.o $(DEFINES)
	
Utils.o: Utils.cpp
	$(CC)  -c Utils.cpp -o Utils.o $(DEFINES)

.PHONY: clean
clean:
	rm -f *.o mandelbrot.run data.txt result.png *.clog2 *.slog2