CFLAGS= -Wall -fpic -coverage -lm -std=c99
runTest: testme.c
	gcc -o testme -g testme.c $(CFLAGS)
	./testme
	gcov -b testme.c
	echo testme.c.gcov
