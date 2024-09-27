#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

inline int OPEN(const char *path, int flag){
    int ret = open(path, flag, 0664);
    if(ret == -1){
        perror("open()");
        exit(1);
    }
    return ret;
}

inline void CLOSE(int fd){
    int ret = close(fd);
    if(ret == -1){
        perror("close()");
        exit(1);
    }
}

int main(){
    int fd = OPEN("./example.txt", O_RDWR | O_CREAT);

    off_t new_offset = lseek(fd, 10, SEEK_SET);
    if (new_offset == -1) {
        perror("lseek()");
        CLOSE(fd);
        return 1;
    }

    int ret = write(fd, "", 1);
    if(ret == -1){
        perror("write()");
        CLOSE(fd);
        return 1;
    }
    
    printf("New offset: %ld\n", (long)new_offset);

    CLOSE(fd);
    return 0;
}