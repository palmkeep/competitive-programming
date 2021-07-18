EXE=a.out
CC=g++
CFLAGS=-g -lm -O2 -std=gnu++17 -Wall -Wextra -Weffc++
OBJ=main.cpp

.PHONY: run
run: $(EXE)
	./$(EXE) <d0

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ -static $(OBJ)

.PHONY: clean
clean:
	rm -rf $(EXE)

