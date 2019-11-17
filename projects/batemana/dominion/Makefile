CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

randomtest_helpers.o: randomtest_helpers.h randomtest_helpers.c
	gcc -c randomtest_helpers.c -g $(CFLAGS)

testrandomizer: randomtest_helpers.o dominion.o rngs.o interface.o
	gcc -o testrandomizer test_gamestate_randomizer.c dominion.o rngs.o interface.o randomtest_helpers.o $(CFLAGS)

randomtests: randomtestcard1.c randomtestcard2.c randomtestcard3.c dominion.o rngs.o interface.o randomtest_helpers.o
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o interface.o randomtest_helpers.o $(CFLAGS)
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o interface.o randomtest_helpers.o $(CFLAGS)
	gcc -o randomtestcard3 randomtestcard3.c -g dominion.o rngs.o interface.o randomtest_helpers.o $(CFLAGS)

randomtestresults: randomtests
	./randomtestcard1 >> randomtests.out
	#./randomtestcard2 >> randomtests.out
	#./randomtestcard3 >> randomtests.out
	gcov -b -f dominion.c >> randomtests.out
	cat dominion.c.gcov >> randomtests.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o randomtestcard1 randomtestcard1.exe randomtestcard2 randomtestcard2.exe randomtestcard3 randomtestcard3.exe testrandomizer testrandomizer.exe playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
