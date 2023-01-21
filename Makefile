CC = g++
CFLAGS = -Wall -Werror -g

all: build

build: main

main: main.o
	$(CC) $(CFLAGS) -o $@ $^
run: build
	./main $(problem)

clean:
	rm -f main main.o