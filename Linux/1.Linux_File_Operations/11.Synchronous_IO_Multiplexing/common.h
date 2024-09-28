#include "header.h"

int open_fifo(const char* path, int flags) {
    int fd = open(path, flags);
    ERROR_CHECK(fd, -1, "open()");
    return fd;
}

int close_fifo(int fd) {
    int ret = close(fd);
    ERROR_CHECK(ret, -1, "close()");
    return ret;
}

int handle_communication(int read_fd, int write_fd) {
    fd_set rdset;
    int rfds[] = {STDIN_FILENO, read_fd};
    int size = sizeof(rfds) / sizeof(rfds[0]);

    struct timeval timeout;
    time_t last_active_time;
    time_t cur_time;
    time(&last_active_time);
    time(&cur_time);

    char io_buf[128];

    while (1) {
        memset(io_buf, 0, sizeof(io_buf));
        FD_ZERO(&rdset);
        for (int i = 0; i < size; i++) FD_SET(rfds[i], &rdset);

        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        int ret = select(read_fd + 1, &rdset, NULL, NULL, &timeout);
        ERROR_CHECK(ret, -1, "select()");

        if (ret > 0) {
            if (FD_ISSET(STDIN_FILENO, &rdset)) {
                ret = read(STDIN_FILENO, io_buf, sizeof(io_buf));
                ERROR_CHECK(ret, -1, "read()");
                if (ret == 0) {
                    ret = write(write_fd, "bye bye", 7);
                    ERROR_CHECK(ret, -1, "write()");
                    break;
                }
                time_t now = time(NULL);
                char* time_buf = ctime(&now);

                char new_buf[1024];
                sprintf(new_buf, "%smsg: %s", time_buf, io_buf);
                ret = write(write_fd, new_buf, strlen(new_buf));
                ERROR_CHECK(ret, -1, "write()");
            } else if (FD_ISSET(read_fd, &rdset)) {
                time(&last_active_time);
                ret = read(read_fd, io_buf, sizeof(io_buf));
                ERROR_CHECK(ret, -1, "read()");
                if (ret == 0) {
                    printf("peer quit\n");
                    break;
                }
                printf("peer send: %.*s\n", ret, io_buf);
            }
        }
        
        {
            time(&cur_time);
            unsigned long long diff = cur_time - last_active_time;
            if (diff > DISCONNECT_TIME) {
                printf("peer time out\n");

                char* time_buf = ctime(&cur_time);
                ret = write(write_fd, time_buf, strlen(time_buf));
                ERROR_CHECK(ret, -1, "write()");
                ret = write(write_fd, "you are disconnected", 20);
                ERROR_CHECK(ret, -1, "write()");
                break;
            }
        }
    }

    close_fifo(read_fd);
    close_fifo(write_fd);

    return 0;
}