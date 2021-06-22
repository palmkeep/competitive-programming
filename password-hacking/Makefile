EXE=a.out
CC=g++
CFLAGS=-lm -lcrypt -O2 -std=c++11 -Wall -Wextra -Werror -pipe -DONLINE_JUDGE
OBJ=main.cpp

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

.PHONY: clean
clean:
	rm -rf $(EXE)
