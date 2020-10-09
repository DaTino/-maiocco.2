CC=gcc
CFLAGS=-I.

all: master palindromes

master: master.o
	$(CC) -o master master.o

palindromes: palindromes.o
	$(CC) -o palindromes palindromes.o

clean:
	rm master palindromes master.o palindromes.o palindromeResults.txt
