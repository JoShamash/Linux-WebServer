#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[]){
    time_t curTime;
    time(&curTime);

    struct tm* localTime = localtime(&curTime);

    if(argc == 2){
        printf("Current time: %04d-%02d-%02d %02d:%02d:%02d\n",
            localTime->tm_year + 1900,
            localTime->tm_mon + 1,
            localTime->tm_mday,
            localTime->tm_hour,
            localTime->tm_min,
            localTime->tm_sec);
    }else{
        printf("Current time: %02d:%02d:%02d\n",
           localTime->tm_hour,
           localTime->tm_min,
           localTime->tm_sec);
    }

    return 0;
}