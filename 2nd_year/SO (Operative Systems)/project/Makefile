CC = gcc
CFLAGS = -Wall -g  -Wextra -pedantic -lm
PKG = `pkg-config --cflags --libs glib-2.0`

all: folders server client

server: bin/monitor

client: bin/tracer

utils: bin/utils

folders:
	@mkdir -p src obj bin tmp

bin/monitor: obj/monitor.o obj/utils.o
	$(CC) -o bin/monitor -g obj/monitor.o obj/utils.o $(PKG)

bin/tracer: obj/tracer.o obj/utils.o
	$(CC) -o bin/tracer -g obj/tracer.o obj/utils.o $(PKG)

bin/utils: obj/utils.o
	$(CC) -o bin/utils -g obj/utils.o $(PKG)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(PKG)

clean:
	@echo "Cleaning..."
	rm -rf bin/*
	rm -rf obj/*.o
