CC = mpicc
DEFINES =
INCL_PATHS =
LIB_PATHS =
LIBRARIES = -lm

all: mandelbrot.run

mpelogs: LIBRARIES += -lmpe
mpelogs: DEFINES += -D MPE_LOGS
mpelogs: mandelbrot.run

mandelbrot.run: main.cpp Board.o Client.o Server.o Config.o Utils.o
	$(CC) main.cpp Board.o Client.o Server.o Config.o Utils.o -o mandelbrot.run $(INCL_PATHS) $(LIB_PATHS) $(LIBRARIES) $(DEFINES)

Board.o: Board.cpp
	$(CC)  -c Board.c -o Board.o $(INCL_PATHS) $(DEFINES)
	
Client.o: Client.cpp
	$(CC)  -c Client.c -o Client.o $(INCL_PATHS) $(DEFINES)
	
Server.o: Server.cpp
	$(CC)  -c Server.c -o Server.o $(INCL_PATHS) $(DEFINES)
	
Config.o: Config.cpp
	$(CC)  -c Config.c -o Config.o $(INCL_PATHS) $(DEFINES)
	
Utils.o: Utils.cpp
	$(CC)  -c Utils.c -o Utils.o $(INCL_PATHS) $(DEFINES)

.PHONY: clean
clean:
	rm -f *.o mandelbrot.run data.txt result.png *.clog2 *.slog2