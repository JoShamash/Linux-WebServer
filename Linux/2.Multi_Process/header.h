#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdbool.h>

#define DISCONNECT_TIME 10 // 断连时间

#define ARGS_CHECK(argc, num)\
    {\
        if(argc != num){\
            fprintf(stderr, "args error!\n");\
            return -1;\
        }\
    }

#define ERROR_CHECK(ret, num, msg)\
    {\
        if(ret == num){\
            perror(msg);\
            return -1;\
        }\
    }

#define TAB       "│   "
#define BLANK     "    "
#define ARROW     "├── "
#define LASTARROW "└── "

#endif // HEADER_H