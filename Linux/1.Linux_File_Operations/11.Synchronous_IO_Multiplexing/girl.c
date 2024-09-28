#include "header.h"
#include "common.h"

int main(int argc, char* argv[]) {
    ARGS_CHECK(argc, 3);

    int fifo_fdr = open_fifo(argv[1], O_RDONLY);
    ERROR_CHECK(fifo_fdr, -1, "open()");
    printf("girl open boy.pipe read_fd\n");

    int fifo_fdw = open_fifo(argv[2], O_WRONLY);
    if (fifo_fdw == -1) {
        close_fifo(fifo_fdr);
        return -1;
    }
    printf("girl open girl.pipe write_fd\n");

    printf("girl is ready\n");
    printf("Press any key to continue...\n");
    getchar();

    time_t now = time(NULL);
    char* time_buf = ctime(&now);
    printf("%sconnected!\n", time_buf);
    
    int ret = handle_communication(fifo_fdr, fifo_fdw);
    if(ret == -1){
        close_fifo(fifo_fdw);
        close_fifo(fifo_fdr);
    }

    return 0;
}