#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int arc, char** argv) {
    const int File_max = 1024;
    int fd = open(argv[1], O_RDONLY);
    char buf[File_max];
    int bytesRead;
    int wordCount = 0;
    int charCount = 0;
    int newLineCount = 0;
    int isWord = 0;
    char last;
    while((bytesRead = read(fd, buf, File_max)) > 0) {
        for(int i=0; i < bytesRead; i++) {
            charCount++;
            if(!isspace(buf[i])) {
                isWord = 1;
            } else { 
                wordCount += isWord;
                isWord = 0;
            }

            if (buf[i] == '\n') {
                newLineCount++;
            }

        }
    } 

    if (isWord == 1) {
        wordCount++;
    }
    close(fd);

    char fullString[10];
    char wordCountString[10];
    char charCountString[10];
    snprintf(fullString, 10, "%d", newLineCount);
    snprintf(wordCountString, 10, "%d", wordCount);
    snprintf(charCountString, 10, "%d", charCount);
    
    strcat(fullString, " ");
    strcat(fullString, wordCountString);
    strcat(fullString, " ");
    strcat(fullString, charCountString);
    strcat(fullString, " ");
    strcat(fullString, argv[1]);
    strcat(fullString, "\n");

    write(1, fullString, strlen(fullString));
}