#include "../header.h"

int main(){
    int ret;
    int fds[2];
    ret = pipe(fds);
    ERROR_CHECK(ret, -1, "pipe");

    pid_t pid = fork();
    if(pid){
        ret = close(fds[1]);
        ERROR_CHECK(ret, -1, "close");

        char buf[128];
        ret = read(fds[0], buf, sizeof(buf));
        ERROR_CHECK(ret, -1, "read");
        puts(buf);
        exit(0);
    }else{
        ret = close(fds[0]);
        ERROR_CHECK(ret, -1, "close");

        char msg[128];
        sprintf(msg, "Child msg: pid=%d, ppid=%d\n", getpid(), getppid());
        ret = write(fds[1], msg, strlen(msg));
        ERROR_CHECK(ret, -1, "read");
        exit(0);
    }

    return 0;
}