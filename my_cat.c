#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char** argv) {
    const int File_max = 1024;
    if(argc < 2) {
        return 1;
    } else {
        for(int i = 1; i < argc; i++) {


            int fd = open(argv[i], O_RDONLY);
            if ( fd < 0 ) {
              return 1;
            }

            char buf[File_max];
            int bytesRead;
            while((bytesRead = read(fd, buf, File_max)) > 0) {
                write(1, buf, bytesRead);
            }

        close(fd);
        }
    }

    return 0;
}
