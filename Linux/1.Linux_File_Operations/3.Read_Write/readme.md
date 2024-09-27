# Linux 系统调用文档：`read`、`pread`、`readv`、`preadv`、`write`

本文档总结了 Linux 下 `read`、`pread`、`readv`、`preadv` 和 `write` 系统调用的使用方法，包括其功能描述、语法、参数说明、返回值及示例。

---

## 1. `read` 系统调用

### 描述
`read` 系统调用用于从文件描述符 `fd` 指定的文件中读取数据到缓冲区 `buf` 中。它是最基本的文件读取操作，适用于顺序读取数据。

### 语法
```c
#include <sys/types.h>
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t nbytes);
```

### 参数

- **`fd`**: 要读取的文件描述符。通常由 `open` 或相关系统调用返回。
- **`buf`**: 指向接收数据的缓冲区的指针。
- **`nbytes`**: 要读取的字节数。

### 返回值

- **成功**：返回实际读取的字节数（可能小于 `nbytes`）。
- **到达文件末尾（EOF）**：返回 `0`。
- **失败**：返回 `-1`，并设置 `errno` 以指示错误原因。

### 示例
```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buffer[100];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    buffer[bytesRead] = '\0'; // 确保字符串终止
    printf("Read %zd bytes: %s\n", bytesRead, buffer);

    close(fd);
    return 0;
}
```

---

## 2. `pread` 系统调用

### 描述
`pread` 系统调用类似于 `read`，但它允许在读取数据时指定文件偏移量，而不会改变文件描述符的当前偏移量。这对于多线程环境尤其有用，可以避免竞态条件。

### 语法
```c
#include <sys/types.h>
#include <unistd.h>

ssize_t pread(int fd, void *buf, size_t nbytes, off_t offset);
```

### 参数

- **`fd`**: 要读取的文件描述符。
- **`buf`**: 指向接收数据的缓冲区的指针。
- **`nbytes`**: 要读取的字节数。
- **`offset`**: 文件中的字节偏移量，从该位置开始读取。

### 返回值

- **成功**：返回实际读取的字节数（可能小于 `nbytes`）。
- **到达文件末尾（EOF）**：返回 `0`。
- **失败**：返回 `-1`，并设置 `errno` 以指示错误原因。

### 示例
```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buffer[100];
    off_t offset = 10; // 从第 10 字节开始读取
    ssize_t bytesRead = pread(fd, buffer, sizeof(buffer) - 1, offset);
    if (bytesRead == -1) {
        perror("pread");
        close(fd);
        return 1;
    }

    buffer[bytesRead] = '\0'; // 确保字符串终止
    printf("Read %zd bytes from offset %ld: %s\n", bytesRead, (long)offset, buffer);

    close(fd);
    return 0;
}
```

---

## 3. `readv` 系统调用

### 描述
`readv` 系统调用用于从文件描述符 `fd` 仅读取数据，并将数据分散存放到多个缓冲区中。它支持向量化 I/O，可以在一次系统调用中读取数据到多个非连续的内存区域，提高效率。

### 语法
```c
#include <sys/uio.h>
#include <unistd.h>

ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
```

### 参数

- **`fd`**: 要读取的文件描述符。
- **`iov`**: 指向 `iovec` 结构数组的指针。每个 `iovec` 结构描述一个缓冲区。
- **`iovcnt`**: `iovec` 结构的数量。

### `struct iovec` 结构
```c
struct iovec {
    void  *iov_base;    // 指向缓冲区的起始地址
    size_t iov_len;     // 缓冲区的长度
};
```

### 返回值

- **成功**：返回实际读取的字节数（可能小于请求的总字节数）。
- **到达文件末尾（EOF）**：返回 `0`。
- **失败**：返回 `-1`，并设置 `errno` 以指示错误原因。

### 示例
```c
#include <fcntl.h>
#include <unistd.h>
#include <sys/uio.h>
#include <stdio.h>

int main() {
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buffer1[50];
    char buffer2[50];
    struct iovec iov[2];
    
    iov[0].iov_base = buffer1;
    iov[0].iov_len = sizeof(buffer1);
    iov[1].iov_base = buffer2;
    iov[1].iov_len = sizeof(buffer2);

    ssize_t bytesRead = readv(fd, iov, 2);
    if (bytesRead == -1) {
        perror("readv");
        close(fd);
        return 1;
    }

    // 确保每个缓冲区以 null 结尾
    if (bytesRead > 0) {
        size_t first_part = bytesRead < sizeof(buffer1) ? bytesRead : sizeof(buffer1) - 1;
        buffer1[first_part] = '\0';
        if (bytesRead > sizeof(buffer1)) {
            size_t second_part = (bytesRead - sizeof(buffer1)) < sizeof(buffer2) ? (bytesRead - sizeof(buffer1)) : sizeof(buffer2) - 1;
            buffer2[second_part] = '\0';
        } else {
            buffer2[0] = '\0';
        }
    }

    printf("Buffer1: %s\nBuffer2: %s\n", buffer1, buffer2);

    close(fd);
    return 0;
}
```

---

## 4. `preadv` 系统调用

### 描述
`preadv` 系统调用结合了 `pread` 和 `readv` 的功能，允许在指定的文件偏移量处，将数据分散读取到多个缓冲区中。这在需要同时从文件的不同位置读取多个数据块时非常有用。

### 语法
```c
#include <sys/uio.h>
#include <unistd.h>

ssize_t preadv(int fd, const struct iovec *iov, int iovcnt, off_t offset);
```

### 参数

- **`fd`**: 要读取的文件描述符。
- **`iov`**: 指向 `iovec` 结构数组的指针。
- **`iovcnt`**: `iovec` 结构的数量。
- **`offset`**: 文件中的字节偏移量，从该位置开始读取。

### 返回值

- **成功**：返回实际读取的字节数。
- **到达文件末尾（EOF）**：返回 `0`。
- **失败**：返回 `-1`，并设置 `errno` 以指示错误原因。

### 示例
```c
#include <fcntl.h>
#include <unistd.h>
#include <sys/uio.h>
#include <stdio.h>

int main() {
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buffer1[50];
    char buffer2[50];
    struct iovec iov[2];
    
    iov[0].iov_base = buffer1;
    iov[0].iov_len = sizeof(buffer1);
    iov[1].iov_base = buffer2;
    iov[1].iov_len = sizeof(buffer2);

    off_t offset = 100; // 从第 100 字节开始读取
    ssize_t bytesRead = preadv(fd, iov, 2, offset);
    if (bytesRead == -1) {
        perror("preadv");
        close(fd);
        return 1;
    }

    // 确保每个缓冲区以 null 结尾
    if (bytesRead > 0) {
        size_t first_part = bytesRead < sizeof(buffer1) ? bytesRead : sizeof(buffer1) - 1;
        buffer1[first_part] = '\0';
        if (bytesRead > sizeof(buffer1)) {
            size_t second_part = (bytesRead - sizeof(buffer1)) < sizeof(buffer2) ? (bytesRead - sizeof(buffer1)) : sizeof(buffer2) - 1;
            buffer2[second_part] = '\0';
        } else {
            buffer2[0] = '\0';
        }
    }

    printf("Buffer1: %s\nBuffer2: %s\n", buffer1, buffer2);

    close(fd);
    return 0;
}
```

---

## 5. `write` 系统调用

### 描述
`write` 系统调用用于将数据从用户空间的缓冲区 `buf` 写入到文件描述符 `fd` 指定的文件中。它是最基本的文件写入操作，适用于顺序写入数据。

### 语法
```c
#include <sys/types.h>
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count);
```

### 参数

- **`fd`**: 要写入的文件描述符。通常由 `open` 或相关系统调用返回。
- **`buf`**: 指向包含要写入数据的缓冲区的指针。
- **`count`**: 要写入的字节数。

### 返回值

- **成功**：返回实际写入的字节数（可能小于 `count`）。
- **失败**：返回 `-1`，并设置 `errno` 以指示错误原因。

### 示例
```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    int fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    const char *data = "Hello, World!\n";
    size_t length = strlen(data);

    ssize_t bytesWritten = write(fd, data, length);
    if (bytesWritten == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    printf("Wrote %zd bytes to output.txt\n", bytesWritten);

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}
```

---

## 注意事项

- **错误处理**：每次系统调用后，应检查返回值是否为 `-1`，并根据 `errno` 进行错误处理。
- **缓冲区大小**：确保提供的缓冲区大小足够存放读取或写入的数据，以避免缓冲区溢出或数据截断。
- **文件偏移量**：
  - `read` 和 `write` 会修改文件描述符的当前偏移量。
  - `pread` 和 `preadv` 不会修改文件描述符的当前偏移量，因此适合多线程环境下的并发读取。
- **分散与聚集 I/O**：`readv` 和 `writev` 适用于需要同时填充或写入多个缓冲区的场景，可以减少系统调用次数，提高性能。
- **权限管理**：在使用 `write` 创建或修改文件时，确保正确设置文件权限，避免权限过宽导致的安全问题。
- **性能优化**：对于大量小块数据的读取或写入，使用向量化 I/O（`readv`、`preadv`、`writev`）可以显著提高性能。

---
