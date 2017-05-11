CC = mpicxx
DEFINES =
INCL_PATHS =
LIB_PATHS =

all: mandelbrot.run

mpelogs: LIBRARIES += -lmpe -lpthread
mpelogs: DEFINES += -D MPE_LOGS
mpelogs: mandelbrot.run

examples: 
	./examples.sh

mandelbrot.run: main.cpp Board.o Client.o Server.o Config.o Utils.o
	$(CC) main.cpp Board.o Client.o Server.o Config.o Utils.o -o mandelbrot.run $(INCL_PATHS) $(LIB_PATHS) $(LIBRARIES) $(DEFINES)

Board.o: Board.cpp
	$(CC)  -c Board.cpp -o Board.o $(INCL_PATHS) $(DEFINES)
	
Client.o: Client.cpp
	$(CC)  -c Client.cpp -o Client.o $(INCL_PATHS) $(DEFINES)
	
Server.o: Server.cpp
	$(CC)  -c Server.cpp -o Server.o $(INCL_PATHS) $(DEFINES)
	
Config.o: Config.cpp
	$(CC)  -c Config.cpp -o Config.o $(INCL_PATHS) $(DEFINES)
	
Utils.o: Utils.cpp
	$(CC)  -c Utils.cpp -o Utils.o $(INCL_PATHS) $(DEFINES)

.PHONY: clean
clean:
	rm -f *.o mandelbrot.run data.txt result.png *.png *.clog2 *.slog2 
