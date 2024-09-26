#ifndef GET_TIME_HPP
#define GET_TIME_HPP

#include <ctime>
#include <cstring>

void get_realtime(char* rtime) {
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    strftime(rtime, 100, "%Y-%m-%d %H:%M:%S", localTime);
    strcat(rtime, "\n");
}

#endif // GET_TIME_HPP
