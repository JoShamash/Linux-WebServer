#include "../header.h"

int main(){
    pid_t pid = fork();
    if(pid == 0){
        while(1){
            printf("I am child!\n");
            sleep(1);
        }
    }else{
        printf("I am parent!\n");
    }
    return 0;
}