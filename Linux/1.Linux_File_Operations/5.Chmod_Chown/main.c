#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(){
    int ret = 0;
    
    ret = chmod("example.txt", 0666);
    if(ret == -1){
        perror("chmod()");
        return 1;
    }

    ret = chown("example.txt", 1001, 1001);
    if(ret == -1){
        perror("chown()");
        return 1;
    }

    return 0;
}