#include <fcntl.h>
#include <cstdio>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    // 创建文件，获取其文件描述符
    int fd = open("example.txt", O_RDWR | O_CREAT | O_TRUNC, 0664);
    if(fd == -1){
        perror("open()");
        return 1;
    }

    // 打开一个目录，获取其文件描述符
    int dirfd = open("./", O_RDONLY);
    if (dirfd == -1) {
        perror("open()");
        return 1;
    }

    // 使用 openat 在指定目录中打开或创建文件
    int fd1 = openat(dirfd, "new_example.txt", O_RDWR | O_CREAT | O_TRUNC, 0664);
    if (fd1 == -1) {
        perror("openat()");
        close(dirfd);
        return 1;
    }

    int ret = close(fd);
    if(ret == -1){
        perror("close()");
        return 1;
    }

    ret = close(fd1);
    if(ret == -1){
        perror("close()");
        return 1;
    }

    return 0;
}