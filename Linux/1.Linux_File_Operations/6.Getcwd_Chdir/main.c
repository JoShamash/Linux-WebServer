#include <stdio.h>
#include <unistd.h>

int main(){
    int ret = 0;
    char buf[128];
    getcwd(buf, sizeof(buf));
    if(ret == -1){
        perror("getcwd()");
        return 1;
    }

    printf("cur dir: %s\n", buf);

    ret = chdir("../");
    if(ret == -1){
        perror("chdir()");
        return 1;
    }

    getcwd(buf, sizeof(buf));
    if(ret == -1){
        perror("getcwd()");
        return 1;
    }

    printf("cur dir: %s\n", buf);

    return 0;
}