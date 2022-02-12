CC=gcc
CFLAGS=-Wall -g -o
MODULES_PATH= src/includes/modules/
MODULES= $(MODULES_PATH)commit.c $(MODULES_PATH)user.c $(MODULES_PATH)repo.c
FILES=$(MODULES) src/includes/parser.c src/includes/hashtable.c src/includes/queries/queries.c
TARGET=teste

guiao-1:
	@echo "Compiling"
	cc $(FILES) main.c $(CFLAGS) $(TARGET)
clean:
	rm $(TARGET)
