#include "../header.h"

int main(){
    pid_t pid = fork();
    if(pid){
        pid_t wait_pid = wait(NULL);
        printf("pid(%d) have been reclaimed\n", pid);
    }else{
        printf("I am child\n");
    }
    return 0;
}