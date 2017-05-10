CC = mpicxx
DEFINES =
INCLUDES =
LIBRARIES =

all: mandelbrot.run

mpelogs: LIBRARIES += -lmpe
mpelogs: DEFINES += -D MPE_LOGS
mpelogs: mandelbrot.run

mandelbrot.run: main.cpp Board.o Client.o Server.o Config.o Utils.o
	$(CC) main.cpp Board.o Client.o Server.o Config.o Utils.o -o mandelbrot.run $(LIBRARIES) $(INCLUDES) $(DEFINES)

Board.o: Board.cpp
	$(CC)  -c Board.cpp -o Board.o $(INCLUDES) $(DEFINES)
	
Client.o: Client.cpp
	$(CC)  -c Client.cpp -o Client.o $(INCLUDES) $(DEFINES)
	
Server.o: Server.cpp
	$(CC)  -c Server.cpp -o Server.o $(INCLUDES) $(DEFINES)
	
Config.o: Config.cpp
	$(CC)  -c Config.cpp -o Config.o $(INCLUDES) $(DEFINES)
	
Utils.o: Utils.cpp
	$(CC)  -c Utils.cpp -o Utils.o $(INCLUDES) $(DEFINES)

.PHONY: clean
clean:
	rm -f *.o mandelbrot.run data.txt result.png *.clog2 *.slog2