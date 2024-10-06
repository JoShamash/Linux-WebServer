#include "../header.h"

int main(){
    int ret = 0;
    ret = fork();
    int pid = getpid();
    int ppid = getppid();
    int sid = getsid(0);
    uid_t uid = getuid();
    gid_t gid = getgid();
    if(ret){   
        printf("I am parent, pid:%d, ppid:%d, sid:%d, uid:%d, gid:%d\n", pid, ppid, sid, uid, gid);
    }else{
        printf("I am child, pid:%d, ppid:%d, sid:%d, uid:%d, gid:%d\n", pid, ppid, sid, uid, gid);
    }
    return 0;
}
