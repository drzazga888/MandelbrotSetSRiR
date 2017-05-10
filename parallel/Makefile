CC = mpicc
DEFINES =
INCL_PATHS =
LIB_PATHS =
LIBRARIES = -lm

all: mandelbrot.run

mpelogs: LIBRARIES += -lmpe
mpelogs: DEFINES += -D MPE_LOGS
mpelogs: mandelbrot.run

mandelbrot.run: Board.o Client.o Server.o Config.o Utils.o
	$(CC) main.c Board.o Client.o Server.o Config.o Utils.o -o mandelbrot.run $(INCL_PATHS) $(LIB_PATHS) $(LIBRARIES) $(DEFINES)

Board.o: Board.c
	$(CC)  -c Board.c -o Board.o $(INCL_PATHS) $(DEFINES)
	
Client.o: Client.c
	$(CC)  -c Client.c -o Client.o $(INCL_PATHS) $(DEFINES)
	
Server.o: Server.c
	$(CC)  -c Server.c -o Server.o $(INCL_PATHS) $(DEFINES)
	
Config.o: Config.c
	$(CC)  -c Config.c -o Config.o $(INCL_PATHS) $(DEFINES)
	
Utils.o: Utils.c
	$(CC)  -c Utils.c -o Utils.o $(INCL_PATHS) $(DEFINES)

.PHONY: clean
clean:
	rm -f *.o mandelbrot.run data.txt result.png *.clog2 *.slog2