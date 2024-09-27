#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>

int main(){
    int ret = 0;

    //打开源文件
    int fd = open("readme.md", O_RDWR | O_CREAT, 0664);
    if(fd == -1){
        perror("open()");
        return 1;
    }

    //创建目标文件
    int fd1 = open("copy.md", O_RDWR | O_CREAT, 0664);
    if(fd1 == -1){
        perror("open()");
        return 1;
    }

    //读取源文件
    char read_buf[1024];
    ret = read(fd, read_buf, sizeof(read_buf)-1);
    if(ret == -1){
        perror("read()");
        close(fd);
        close(fd1);
        return 1;
    }

    //写入目标文件
    ret = write(fd1, read_buf, ret);
    if(ret == -1){
        perror("write()");
        close(fd);
        close(fd1);
        return 1;
    }

    ret = close(fd);
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