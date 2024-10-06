#include "../header.h"

int main(){
    char* argv[] = {"-a", NULL};
    int ret = execv("./info", argv);
    ERROR_CHECK(ret, -1, "execl");
    printf("this is not be accessiable!\n");
    return 0;
}