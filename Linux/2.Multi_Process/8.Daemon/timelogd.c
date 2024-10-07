#include "../header.h"

int main(){
    pid_t pid = fork();
    if(pid){
        exit(0);
    }else{
        if (execl("./timed", "./timed", NULL) == -1) {
            perror("execl failed");
            exit(1); // 使用 exit 以确保子进程退出
        }
    }
    return 0;
}