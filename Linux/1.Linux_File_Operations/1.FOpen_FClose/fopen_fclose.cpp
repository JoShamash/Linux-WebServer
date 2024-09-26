/*

FILE* fopen(const char* path, const char* mode);//文件名 模式
int fclose(FILE* stream);

模式 读 写   位置   截断原内容 创建
rb   Y  N   文件头    N       N
rb+  Y  Y   文件头    N       N
wb   N  Y   文件头    Y       Y
wb+  Y  Y   文件头    Y       Y
ab   N  Y   文件尾    N       Y
ab+  Y  Y   文件尾    N       Y

"r"：以只读模式打开文件。文件必须存在。
"w"：以写入模式打开文件。如果文件不存在则创建，存在则清空内容。
"a"：以追加模式打开文件。如果文件不存在则创建，写入数据会追加到文件末尾。
"r+"：以读写模式打开文件。文件必须存在。
"w+"：以读写模式打开文件。如果文件不存在则创建，存在则清空内容。
"a+"：以读写模式打开文件。如果文件不存在则创建，写入数据会追加到文件末尾。
"rb"：以二进制模式只读打开文件。文件必须存在。
"wb"：以二进制模式写入打开文件。如果文件不存在则创建，存在则清空内容。
"ab"：以二进制模式追加打开文件。如果文件不存在则创建。
"rb+"：以二进制模式读写打开文件。文件必须存在。
"wb+"：以二进制模式读写打开文件。如果文件不存在则创建，存在则清空内容。
"ab+"：以二进制模式读写打开文件。如果文件不存在则创建，写入数据会追加到文件末尾。

*/

#include <iostream>
#include <cstring>
#include "gettime.hpp"
#include "RAII.hpp"

using namespace std;

int main() {
    FILE* file = fopen("example.txt", "ab+");
    if (!file) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    RAII<FILE> fp(file);

    char rtime[32];
    get_realtime(rtime);
    fwrite(rtime, strlen(rtime), 1, fp.get());

    return 0;
}