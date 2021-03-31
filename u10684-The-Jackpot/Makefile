EXECUTABLE=tst
CC=g++
CFLAGS=-lm -lcrypt -O2 -std=c++11 -Wall -Wextra -Werror
OBJ=main.cpp

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

.PHONY: clean
clean:
	rm -rf $(EXECUTABLE)
