EXE=a.out
CC=gcc
CFLAGS=-lm -lcrypt -O2 -Wall -Wextra -pipe -DONLINE_JUDGE
OBJ=main.cpp

.PHONY: clean test
test: $(EXE)
	./$(EXE) <d0 | diff --color=always a0 -


$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

clean:
	rm -rf $(EXE)
