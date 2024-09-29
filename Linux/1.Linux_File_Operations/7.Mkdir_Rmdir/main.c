#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    int ret = 0;

    ret = mkdir("new_dir", 0777);
    if(ret == -1){
        perror("mkdir()");
    }

    ret = rmdir("new_dir");
    if(ret == -1){
        perror("rmdir()");
        return 1;
    }

    return 0;
}