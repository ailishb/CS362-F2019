CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

cardEffect.o: cardEffect.h cardEffect.c
	gcc -c cardEffect.c -g $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o cardEffect.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o cardEffect.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittests: unittest1.c unittest2.c dominion.o rngs.o interface.o cardEffect.o 
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o interface.o cardEffect.o $(CFLAGS)
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o interface.o cardEffect.o $(CFLAGS)
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o interface.o cardEffect.o $(CFLAGS)
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o interface.o cardEffect.o $(CFLAGS)
	gcc -o unittest5 unittest5.c -g dominion.o rngs.o interface.o cardEffect.o $(CFLAGS)

unittestresults: unittests
	./unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./unittest5 >> unittestresults.out
	gcov -b -f cardEffect.c >> unittestresults.out
	cat cardEffect.c.gcov >> unittestresults.out

randomtest_helpers.o: randomtest_helpers.h randomtest_helpers.c
	gcc -c randomtest_helpers.c -g $(CFLAGS)

randomtests: randomtestcard1.c randomtestcard2.c randomtestcard3.c dominion.o rngs.o interface.o randomtest_helpers.o cardEffect.o
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o interface.o randomtest_helpers.o cardEffect.o $(CFLAGS)
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o interface.o randomtest_helpers.o cardEffect.o $(CFLAGS)
	gcc -o randomtestcard3 randomtestcard3.c -g dominion.o rngs.o interface.o randomtest_helpers.o cardEffect.o $(CFLAGS)

randomtestresults: randomtests
	./randomtestcard1 >> randomtests.out
	./randomtestcard2 >> randomtests.out
	./randomtestcard3 >> randomtests.out
	gcov -b -f cardEffect.c >> randomtests.out
	cat cardEffect.c.gcov >> randomtests.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o cardEffect.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe randomtestcard1 randomtestcard1.exe randomtestcard2 randomtestcard2.exe randomtestcard3 randomtestcard3.exe unittest1 unittest1.exe unittest2 unittest2.exe unittest3 unittest3.exe unittest4 unittest4.exe unittest5 unittest5.exe *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
