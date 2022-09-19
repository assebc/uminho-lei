CC = gcc
CFLAGS = -Wall -O0 -g -o
MODULES_PATH_COMMITS = src/includes/modules/commits/
MODULES_PATH_USERS = src/includes/modules/users/
MODULES_PATH_REPOS = src/includes/modules/repos/
MODULES_1 = $(MODULES_PATH_COMMITS)commit.c $(MODULES_PATH_USERS)user.c $(MODULES_PATH_REPOS)repo.c
MODULES_2 = $(MODULES_PATH_COMMITS)commits.c $(MODULES_PATH_USERS)users.c $(MODULES_PATH_REPOS)repos.c
FILES = $(MODULES_1) $(MODULES_2) src/includes/parser.c src/includes/parsing.c src/includes/hashtable/hashtable.c src/includes/linkedlist.c src/includes/queries/queries.c src/includes/interface.c
TARGET = guiao-3
TARGET_F = saida

main:
	@echo "Compiling"
	cc $(FILES) src/main.c $(CFLAGS) $(TARGET)

clean:
	rm -r $(TARGET_F) $(TARGET)
