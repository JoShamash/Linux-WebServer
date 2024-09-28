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

    fd_set rdset; // 设置读事件集合
    int rfds[] = {STDIN_FILENO, fifo_fdr}; // 用于读的文件描述符集合
    int size = sizeof(rfds) / sizeof(rfds[0]);

    struct timeval timeout; // 设置超时检查时间
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    clock_t last_active_time = clock(); // gilr最后活跃时间
    clock_t cur_time = clock(); // 当前时间

    char io_buf[128];

    while(1){ //循环读写
        memset(io_buf, 0, sizeof(io_buf));

        FD_ZERO(&rdset); // 事件初始化
        for(int i = 0; i < size; i++) FD_SET(rfds[i], &rdset); // 加入监听
        int ret = select(fifo_fdr+1, &rdset, NULL, NULL, &timeout); // select阻塞进程，开始轮询，rdset返回的是就绪事件
        ERROR_CHECK(ret, -1, "select()");
        if(ret > 0){ // 未超时
            if(FD_ISSET(STDIN_FILENO, &rdset)){ // stdin就绪
                ret = read(STDIN_FILENO, io_buf, sizeof(io_buf)); //读取stdin
                ERROR_CHECK(ret, -1, "read()");
                if(ret == 0){ // ctrl+d 主动结束通信
                    ret = write(fifo_fdw, "bye bye", 7); //写入boy.pipe
                    ERROR_CHECK(ret, -1, "write()");
                    break;
                }
                ret = write(fifo_fdw, io_buf, ret); //写入boy.pipe
                ERROR_CHECK(ret, -1, "write()");
            }else if(FD_ISSET(fifo_fdr, &rdset)){ // fifo_fdr就绪
                last_active_time = clock(); // 更新gilr最后活跃时间

                ret = read(fifo_fdr, io_buf, sizeof(io_buf)); // 读取girl.pipe
                ERROR_CHECK(ret, -1, "read()");
                if(ret == 0){ // 对方结束通信本地也结束，如果不结束则循环输出：girl send: 
                    printf("girl quit\n");
                    break;
                }
                printf("girl send: %.*s\n", ret, io_buf); // 接收消息
            }   
        }else{ // 超时 获取当前时间
            cur_time = clock();
            double diff = ((double) (cur_time - last_active_time)) / CLOCKS_PER_SEC; // 未活跃时间
            if(diff > DISCONNECT_TIME){ // 断连
                printf("girl time out\n");
                ret = write(fifo_fdw, "you are disconnected", 20); //写入boy.pipe
                ERROR_CHECK(ret, -1, "write()");
                break;
            }
        }

    }

    ret = close(fifo_fdr);
    ERROR_CHECK(ret, -1, "close()");
    ret = close(fifo_fdw);
    ERROR_CHECK(ret, -1, "close()");

    return 0;
}