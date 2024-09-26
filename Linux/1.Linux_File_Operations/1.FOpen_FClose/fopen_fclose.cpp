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