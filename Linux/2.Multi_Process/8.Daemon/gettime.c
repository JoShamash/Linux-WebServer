#include "../header.h"

void Daemon(){
    const int MAXFD = 65535;
    setsid();
    chdir("/");
    umask(002);
    for(int i = 0; i < MAXFD; i++){
        close(i);
    }
    int fd = open("/dev/null", O_RDWR);
    dup2(fd, STDIN_FILENO);
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);
    close(fd);
}

int main(){
    Daemon();

    int fd = open("./time.info", O_RDWR | O_CREAT | O_APPEND, 0664);
    char buf[1024];
    time_t curTime;
    while(1){
        time(&curTime);
        struct tm* localTime = localtime(&curTime);
        memset(buf, sizeof(char), sizeof(buf));
        sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d\n",
            localTime->tm_year + 1900,
            localTime->tm_mon + 1,
            localTime->tm_mday,
            localTime->tm_hour,
            localTime->tm_min,
            localTime->tm_sec);
        write(fd, buf, strlen(buf));
        sleep(1);
    }
    return 0;
}