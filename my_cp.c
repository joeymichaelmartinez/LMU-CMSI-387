#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <libgen.h>
    
    void copy(int argc, char** argv) {
        struct stat path_stat;
        stat(argv[2], &path_stat);
        char path_buffer[PATH_MAX+1];
        if(0){
            int readDescriptor = open(argv[1], O_RDONLY);
            int writeDescriptor = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
            const int File_max = 1024;
            char buf[File_max];
            int bytesRead;
            while((bytesRead = read(readDescriptor, buf, File_max)) > 0) {
                write(writeDescriptor, buf, bytesRead);
            }

            close(readDescriptor);
            close(writeDescriptor);
        } else {
            for(int i = 1; i < argc-1; i++) {

                int readDescriptor = open(argv[i], O_RDONLY);
                char fullPath[PATH_MAX];
                strcpy(fullPath, argv[argc-1]);
                strcat(fullPath, basename(argv[i]));
                printf("%s\n", fullPath);
                int writeDescriptor = open(fullPath, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
                printf("%d", writeDescriptor);
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
    }

int main (int argc, char** argv) {
    if(argc < 2) {
        return 1;
    } else {
        copy(argc, argv);
    }
}

