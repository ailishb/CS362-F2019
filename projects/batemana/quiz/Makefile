CFLAGS = -Wall -fpic -coverage -lm -std=c99

testme:
	gcc testme.c -o testme $(CFLAGS)

coverage:
	gcov testme.c

clean:
	rm -f *.o testme.exe testme *.gcov *.gcda *.gcno *.out
