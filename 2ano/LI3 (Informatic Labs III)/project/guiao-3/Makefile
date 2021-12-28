CC=gcc
CFLAGS=-Wall -g -o
MODULES_PATH=includes/modules/
MODULES= $(MODULES_PATH)commit.c $(MODULES_PATH)user.c $(MODULES_PATH)repo.c
FILES=$(MODULES) includes/parser.c includes/hashtable.c includes/queries/queries.c
TARGET=teste

guiao-1:
	@echo "Compiling"
	cc $(FILES) main.c $(CFLAGS) $(TARGET)
clean:
	rm $(TARGET)
