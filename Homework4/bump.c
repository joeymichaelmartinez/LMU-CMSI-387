#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFERSIZE 1024

void execution(char** collectionOfInputs, int numberOfArguments) {
    char bin[2048] = "/bin/"; // figure what to allocate for this
    strcat(bin, collectionOfInputs[0]);
    if (strcmp(collectionOfInputs[0], "cd") == 0) {
        if (numberOfArguments == 1) {
            chdir(getenv("HOME"));
        } else {
            chdir(collectionOfInputs[1]);
        }
    } else {
        // for(int j =0; j < numberOfArguments; j++){
        //     // printf("%s", collectionOfInputs[j]);
        // }
        pid_t pid2 = fork();
        execv(bin, collectionOfInputs);
    }
    
}
// void forkSetup(char** collectionOfInputs, int numberOfArguments) {
    
// }

int main(int argc, char** argv) {
    chdir(getenv("HOME"));
    while (1) {
        char buf[BUFFERSIZE]; // Get proper size for this
        char input[BUFFERSIZE];
        printf("BUMP::%s:: ", getcwd(buf, BUFFERSIZE));
        fgets(input, BUFFERSIZE, stdin);
        char* separatedInputs = strtok(input, " \n");
        char* collectionOfInputs[2048]; // Figure out what space to allocate
        int i = 0;
        while (separatedInputs != NULL) {
            collectionOfInputs[i] = separatedInputs;
            separatedInputs = strtok(NULL, " \n");
            i++;
        }
        collectionOfInputs[i] = '\0'; // Figure out a better way to do this
        if (strcmp(collectionOfInputs[i - 1], "&") == 0) {
            pid_t pid;
            pid = fork();
            if (pid == 0) {
                // pid_t pid2 = fork();
                collectionOfInputs[i - 1] = '\0';
                execution(collectionOfInputs, i - 1);
            } else {
                return 0;
            }
                wait(NULL);
        } else {
            pid_t pid;
            pid = fork();
            if (pid == 0) {
                execution(collectionOfInputs, i);
            }
            wait(NULL);
        }
    }
    return 0;
}