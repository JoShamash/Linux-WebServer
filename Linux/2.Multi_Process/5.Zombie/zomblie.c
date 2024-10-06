#include "../header.h"

int main(){
    pid_t pid = fork();
    if(pid){
        while(1){
            printf("parent exit!\n");
            sleep(1);
        }
    }else{
        printf("child destroy!\n");
    }
    return 0;
}