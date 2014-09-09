.PHONY:clean run
CC=g++
CFLAGS=-Wall
BIN=./bin/main
INCLUDE=-I./include
LIB=-L./lib
OBJS=./obj/Words.o ./obj/Text.o ./obj/Cache.o ./obj/Timer.o ./obj/TimerThread.o ./obj/EchoServer.o ./obj/main.o
$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lpthread $(LIB) -lecho
./obj/%.o:./src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@ $(INCLUDE) -std=c++0x
clean:
	rm -f ./obj/*.o $(BIN)
run:
	$(BIN)
