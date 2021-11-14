$(CC) = gcc

guiao-1:
	$(CC)  src/eval.c src/define.h src/btree.c src/main.c -o guiao-1 exercicio-1
	#$(CC)  src/eval.c src/define.h src/btree.c src/main.c -o guiao-1 exercicio-2

main.o: main.c define.h eval.h btree.h
	$(CC) -c main.c

btree.o: btree.c btree.h
	$(CC) -c btree.c

eval.o: eval.c eval.h
	$(CC) -c eval.c

clean:
	rm guiao-1


