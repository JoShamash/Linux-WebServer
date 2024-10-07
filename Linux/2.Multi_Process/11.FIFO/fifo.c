#include "../header.h"
#define PATH "pipe"
int main(){
    int ret;

    ret = mkfifo(PATH, 0664);
    ERROR_CHECK(ret, -1, "mkfifo");

    pid_t pid = fork();
    if(pid){
        int fdr = open(PATH, O_RDONLY);
        ERROR_CHECK(fdr, -1, "open");

        char buf[128];
        ret = read(fdr, buf, sizeof(buf));
        ERROR_CHECK(ret, -1, "read");
        puts(buf);

        unlink(PATH);
        exit(0);
    }else{
        int fdw = open(PATH, O_WRONLY);
        ERROR_CHECK(fdw, -1, "open");

        char msg[128];
        sprintf(msg, "Child msg: pid=%d, ppid=%d\n", getpid(), getppid());
        ret = write(fdw, msg, strlen(msg));
        ERROR_CHECK(ret, -1, "write");
        exit(0);
    }

    return 0;
}