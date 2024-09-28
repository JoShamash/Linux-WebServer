#include "header.h"

int main(int argc, char* argv[]){
    int ret = 0; //返回值

    ARGS_CHECK(argc, 3); //检查命令行参数个数

    int fifo_fdw = open(argv[1], O_WRONLY);
    ERROR_CHECK(fifo_fdw, -1, "open()");
    printf("boy open boy.pipe write_fd\n");

    int fifo_fdr = open(argv[2], O_RDONLY);
    ERROR_CHECK(fifo_fdr, -1, "open()");
    printf("boy open girl.pipe read_fd\n");

    printf("boy is ready\n");
    printf("Press any key to continue...\n");
    getchar(); // 等待用户输入

    char io_buf[128];

    while(1){ //循环读写
        memset(io_buf, 0, sizeof(io_buf));

        ret = read(STDIN_FILENO, io_buf, sizeof(io_buf)); //读取stdin
        ERROR_CHECK(ret, -1, "read()");
        ret = write(fifo_fdw, io_buf, ret); //写入boy.pipe
        ERROR_CHECK(ret, -1, "write()");

        ret = read(fifo_fdr, io_buf, sizeof(io_buf)); //读取girl.pipe
        ERROR_CHECK(ret, -1, "read()");
        printf("girl send: %.*s\n", ret, io_buf); //接收消息
    }

    ret = close(fifo_fdr);
    ERROR_CHECK(ret, -1, "close()");
    ret = close(fifo_fdw);
    ERROR_CHECK(ret, -1, "close()");

    return 0;
}