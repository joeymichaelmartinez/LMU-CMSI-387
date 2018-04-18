#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define BUFFERSIZE 1024

void execution(char** collectionOfInputs, int numberOfArguments) {
    char bin[BUFFERSIZE] = "/bin/";
    strcat(bin, collectionOfInputs[0]);
    execv(bin, collectionOfInputs);
}

void fork_handler(char** collectionOfInputs, int numberOfArguments) {
    if (!fork()) {
        if(!fork()) {
            collectionOfInputs[numberOfArguments - 1] = '\0';
            execution(collectionOfInputs, numberOfArguments - 1);
        } else {
            exit(0);
        }
    } else {
        wait(NULL);
    }
}

int main(int argc, char** argv) {
    chdir(getenv("HOME"));
    while (1) {
        char buf[BUFFERSIZE]; 
        char input[BUFFERSIZE];
        
        printf("BUMP::%s:: ", getcwd(buf, BUFFERSIZE));
        
        fgets(input, BUFFERSIZE, stdin);
        
        char* separatedInputs = strtok(input, " \n");
        char* collectionOfInputs[BUFFERSIZE];
        
        int i;
        for (i = 0; separatedInputs != NULL; i++) {
            collectionOfInputs[i] = separatedInputs;
            separatedInputs = strtok(NULL, " \n");
        }
        collectionOfInputs[i] = '\0';
        int numberOfArguments = i;
        if (collectionOfInputs[0] != '\0') {  
            if (strcmp(collectionOfInputs[0], "cd") == 0) {
                if (numberOfArguments == 1 || (numberOfArguments == 2 && strcmp(collectionOfInputs[i - 1], "&") == 0)) {
                    chdir(getenv("HOME"));
                } else {
                    chdir(collectionOfInputs[1]);
                }
            } else if (strcmp(collectionOfInputs[0], "sup") == 0) {
                syscall(333, NULL);
            } else if (strcmp(collectionOfInputs[i - 1], "&") == 0) {
                fork_handler(collectionOfInputs, numberOfArguments);
            } else {
                if (!fork()) {
                    execution(collectionOfInputs, i);
                }
                wait(NULL);
            }
        }
    }
    return 0;
}