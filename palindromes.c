#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHMSZ 128

void removeSpaces(char *s);
void removeNonAlphaNum(char *str);

int main(int argc, char **argv) {
	
	//this guy has to open and close a file, I believe...
	//master controls the amount of processes doing the checking.
	int shmid;
	key_t key;
	char *shm, *s;

	

	if (argc < 2) {
		perror("Palindromes: Not enough arguments. Aborting.\n");
		exit(-1);
	}

	//printf("orig %s\n", argv[argc-1]);

	//copy string over to leave original ok, so we can strip punc/ws
	char str[64];
	strcpy(str, argv[argc-1]);

	removeSpaces(str);
	//printf("sans space %s\n", str);

	//strip non alphanumerc chars
	removeNonAlphaNum(str);
	//printf("sans punc %s\n", str);

	
	int l = 0;
	int h = strlen(str)-1;
	while (h > l) {
		if (str[l++] != str[h--])  {
			printf("%s no good\n", str);
			return 0;
		}
	}
	printf("%s FUCK YEAH PALINDROME\n", str);
	return 0;
}

void removeSpaces(char* s) {
    const char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*s++ = *d++);
}

void removeNonAlphaNum(char *str) {
    unsigned long i = 0;
    unsigned long j = 0;
    char c;

    while ((c = str[i++]) != '\0') {
        if (isalnum(c)) {
            str[j++] = c;
        }
    }
    str[j] = '\0';
}
