C_COMPILER := gcc -std=c11
C_OPTIONS  := -Wall -pedantic -g -ggdb
CUNIT      := -lcunit

run: clean httest #clean first, httest after. works well.
	./httest

memtest: clean httest
	valgrind --leak-check=full ./httest

httest: hash_table.o hash_table_test.c
	$(C_COMPILER) $(C_OPTIONS) $(CUNIT) hash_table.o hash_table_test.c -o httest

hash_table.o: hash_table.c hash_table.h
	$(C_COMPILER) $(C_OPTIONS) -c hash_table.c

clean:
	rm -f *.o
	rm -f httest