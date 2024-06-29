C_COMPILER := gcc -std=c11
C_OPTIONS  := -Wall -pedantic -g -ggdb
CUNIT      := -lcunit

httest: hash_table.o hash_table_test.c
	$(C_COMPILER) $(C_OPTIONS) $(CUNIT) hash_table.o hash_table_test.c -o httest

hash_table.o: hash_table.c hash_table.h
	$(C_COMPILER) $(C_OPTIONS) -c hash_table.c