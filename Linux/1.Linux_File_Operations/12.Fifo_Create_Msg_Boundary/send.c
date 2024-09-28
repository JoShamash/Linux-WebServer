#include "header.h"

int main(int argc, char* argv[]){ // ./send.c [pipename] [filename]
    ARGS_CHECK(argc, 3);
    int ret = 0;
    PP send_block;

    int fdw = open(argv[1], O_WRONLY);
    ERROR_CHECK(fdw, -1, "open()");

    send_block.size = strlen(argv[2]); // 文件名长度
    memcpy(send_block.data, argv[2], send_block.size); // 文件名

    // 发送文件名
    ret = write(fdw, &send_block.size, sizeof(send_block.size)); // 发送数据长度
    ERROR_CHECK(ret, -1, "write()");
    ret = write(fdw, send_block.data, send_block.size); // 发送数据
    ERROR_CHECK(ret, -1, "write()");

    // 打开文件流
    int fdr = open(argv[2], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open()");

    // 发送文件内容
    while(1){
        ret = read(fdr, send_block.data, sizeof(send_block.data));
        send_block.size = ret;
        if(ret == 0){
            printf("send completed!\n");
            break;
        }

        ret = write(fdw, &send_block.size, sizeof(send_block.size)); // 发送数据长度
        ERROR_CHECK(ret, -1, "write()");
        ret = write(fdw, send_block.data, send_block.size); // 发送数据
        ERROR_CHECK(ret, -1, "write()");
    }

    ret = close(fdr);
    ERROR_CHECK(ret, -1, "close()");
    ret = close(fdw);
    ERROR_CHECK(ret, -1, "close()");
    
    return 0;
}