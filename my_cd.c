#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv) {
    char path_buffer[PATH_MAX+1];
    if(argc == 1) {
        chdir(getenv("HOME"));
        char* writeStatement = getcwd(path_buffer, PATH_MAX);
        strcat(writeStatement, "\n");
        write(1, writeStatement, strlen(writeStatement));
    } else{
        realpath(argv[1], path_buffer);
        chdir(path_buffer);
        char* writeStatement = getcwd(path_buffer, PATH_MAX);
        strcat(writeStatement, "\n");
        write(1, writeStatement, strlen(writeStatement));
    }
    
    return 0;
}