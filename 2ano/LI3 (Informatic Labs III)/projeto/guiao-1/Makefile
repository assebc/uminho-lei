CC = gcc
CFLAGS = -Wall -g -o
MODULES_PATH = src/
MODULES_1 = $(MODULES_PATH)commit.c $(MODULES_PATH)user.c $(MODULES_PATH)repo.c
MODULES= $(MODULES_PATH)hashtable.c $(MODULES_PATH)eval.c $(MODULES_PATH)parser.c
FILES = $(MODULES_1) $(MODULES)
TARGET = guiao-1
TARGET_2 = saida

guiao-1:
	@echo "Compiling"
	cc $(FILES) src/main.c $(CFLAGS) $(TARGET)

clean:
	rm -r $(TARGET) $(TARGET_2)

