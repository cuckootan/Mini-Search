CC=g++

SOURCES_DIR=./src
INCLUDES_DIR=./include
OBJS_DIR=./obj
BIN_DIR=./bin

CFLAGS=-I$(INCLUDES_DIR) -c -Wall -std=c++0x
LDFLAGS=-lecho -lpthread



SOURCES=$(wildcard $(SOURCES_DIR)/*.cc)

NOTDIR=$(notdir $(SOURCES))
SUBST=$(patsubst %.cc, %.o, $(NOTDIR))
OBJS=$(addprefix $(OBJS_DIR)/, $(SUBST))

BIN=$(BIN_DIR)/main



$(BIN):$(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJS_DIR)/%.o:$(SOURCES_DIR)/%.cc
	$(CC) -o $@ $< $(CFLAGS)



.PHONY:clean run
clean:
	rm -f $(OBJS)
	rm -f $(BIN)
run:
	$(BIN)
