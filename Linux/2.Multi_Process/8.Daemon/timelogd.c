#include "../header.h"

void Daemon(){
    const int MAXFD = 65535;
    setsid();
    chdir("/");
    umask(002);
    for(int i = 0; i < MAXFD; i++)
        close(i);
    int fd = open("/dev/null", O_RDWR);
    dup2(fd, STDIN_FILENO);
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);
    close(fd);
}

int main(){
    pid_t pid = fork();
    if(pid){
        wait(NULL);
    }else{
        Daemon();
        if (execl("./timed", "./timed", NULL) == -1) {
            perror("execl failed");
            _exit(1); // 使用 _exit 以确保子进程退出
        }
    }
    return 0;
}