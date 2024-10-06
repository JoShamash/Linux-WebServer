#include "../header.h"

int main(){
    int ret = execl("./info", "-a", NULL);
    ERROR_CHECK(ret, -1, "execl");
    printf("this is not be accessiable!\n");
    return 0;
}