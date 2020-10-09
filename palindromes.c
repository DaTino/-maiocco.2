#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSZ 128

void removeSpaces(char *s);
void removeNonAlphaNum(char *str);

int main(int argc, char **argv) {

	//this guy has to open and close a file, I believe...
	//master controls the amount of processes doing the checking.
	int shmid;
	key_t key;
	char *shm, *s;

	key = 612;
	//locating...
	if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
		perror("palindromes: error locating shared memory segment.");
		exit(1);
	}
	//attaching...
	if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
		perror("palindromes: error attaching shared memory.");
		exit(1);
	}
	printf("Gonna try printing...\n");
	printf("%s", shm);


	printf("Exiting, bitches\n");
	return 0;

	const char s[3] = "$$";
	char *token;

	token = strtok(shm, s);
	while (token != NULL) {
		char str[64];
		strcpy(str, argv[argc-1]);
		//printf("orig %s\n", argv[argc-1]);

		//copy string over to leave original ok, so we can strip punc/ws
		char str[64];
		strcpy(str, argv[argc-1]);
		removeSpaces(str);
		//printf("sans space %s\n", str);
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

	}
	// if (argc < 2) {
	// 	perror("Palindromes: Not enough arguments. Aborting.\n");
	// 	exit(-1);
	// }

	int l = 0;
	int h = strlen(str)-1;
	while (h > l) {
		if (str[l++] != str[h--])  {
			printf("%s no good\n", str);
			return 0;
		}
	}
	printf("%s FUCK YEAH PALINDROME\n", str);

	*shm = '*';

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
