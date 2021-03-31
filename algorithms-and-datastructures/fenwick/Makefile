EXECUTABLE=a.out
CC=g++
CFLAGS=-g -lm -O2 -std=c++17 -Wall -Wextra
OBJ=main.cpp

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ -static $(OBJ)

.PHONY: clean
clean:
	rm -rf $(EXECUTABLE)

