EXE=whac-a-moler
CC=g++
CFLAGS=-g -O2 -std=gnu++17
LFLAGS=-lm
WFLAGS=-Wall -Wextra -Weffc++ -Wpedantic
OBJ=main.cpp


.PHONY: clean test
test: $(EXE)
	./$(EXE)<d0 | diff --color=always a0 -

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ -static $(OBJ) $(LFLAGS) $(WFLAGS)

clean:
	rm -rf $(EXE)

