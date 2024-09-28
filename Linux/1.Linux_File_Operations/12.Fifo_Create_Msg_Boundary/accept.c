#include "header.h"

int main(int argc, char* argv[]){ // ./accept.c [pipename]
    ARGS_CHECK(argc, 2);
    int ret = 0;
    PP accept_block;

    int fdr = open(argv[1], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open()");

    // 读取文件名
    ret = read(fdr, &accept_block.size, sizeof(accept_block.size));
    ERROR_CHECK(ret, -1, "read()");
    ret = read(fdr, accept_block.data, accept_block.size);
    ERROR_CHECK(ret, -1, "read()");

    // 创建目录与文件
    const char* dir = "new_dir";
    ret = mkdir(dir, 0775);
    ERROR_CHECK(ret, -1, "mkdir()");

    char path[128];
    sprintf(path, "%s/%s", dir, accept_block.data);
    ret = open(path, O_CREAT | O_RDWR | O_TRUNC, 0664);
    ERROR_CHECK(ret, -1, "open()");

    // 打开文件流
    int fdw = open(path, O_WRONLY);
    ERROR_CHECK(fdw, -1, "open()");

    // 读取文件内容
    while(1){
        ret = read(fdr, &accept_block.size, sizeof(accept_block.size));
        ERROR_CHECK(ret, -1, "read()");
        ret = read(fdr, accept_block.data, accept_block.size);
        ERROR_CHECK(ret, -1, "read()");

        if(ret == 0){
            printf("accept completed!\n");
            break;
        }

        ret = write(fdw, accept_block.data, accept_block.size); // 写入数据
        ERROR_CHECK(ret, -1, "write()");
    }

    ret = close(fdr);
    ERROR_CHECK(ret, -1, "close()");
    ret = close(fdw);
    ERROR_CHECK(ret, -1, "close()");

    return 0;
}