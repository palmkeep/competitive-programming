EXE=a.out
CC=g++
CFLAGS=-lm -lcrypt -O2 -std=gnu++17 -Wall -Wextra -Werror -pipe -DONLINE_JUDGE

$(EXE): main.cpp
	$(CC) $(CFLAGS) -o $(EXE) main.cpp

.PHONY: clean
clean:
	rm -rf $(EXE)
