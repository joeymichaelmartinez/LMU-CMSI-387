#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main (int argc, char** argv) {
    if(argc < 2) {
        return 1;
    } else {
        int readDescriptor = open(argv[1], O_RDWR);
        int writeDescriptor = open(argv[2], O_RDWR | O_CREAT);
        if(writeDescriptor < 0) {
            // writeDescriptor = open(argv[2], O_WRONLY);
        }
        printf("%d", writeDescriptor);
        *fopen(argv[2], "w");
        const int File_max = 1024;
        char buf[File_max];
        int bytesRead;
        while((bytesRead = read(readDescriptor, buf, File_max)) > 0) {
            write(writeDescriptor, buf, bytesRead);
        }

        close(readDescriptor);
        close(writeDescriptor);
    }
}