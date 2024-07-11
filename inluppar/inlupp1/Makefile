C_COMPILER := gcc -std=c11
C_OPTIONS  := -Wall -pedantic -g -ggdb
CUNIT      := -lcunit

run: clean lltest #clean first, httest after. works well.
	./lltest

memtest: lltest
	clear
	valgrind --leak-check=full ./lltest

httest: hash_table.o hash_table_test.c
	$(C_COMPILER) $(C_OPTIONS) $(CUNIT) hash_table.o hash_table_test.c -o httest

hash_table.o: hash_table.c hash_table.h
	$(C_COMPILER) $(C_OPTIONS) -c hash_table.c

lltest: linked_list.o linked_list_test.c
	$(C_COMPILER) $(C_OPTIONS) $(CUNIT) linked_list.o linked_list_test.c -o lltest

linked_list.o: linked_list.c linked_list.h
	$(C_COMPILER) $(C_OPTIONS) -c linked_list.c

clean:
	rm -f *.o httest lltest
