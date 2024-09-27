# Linux 系统调用文档：open、openat、close

本文档总结了 Linux 下 `open`、`openat` 和 `close` 系统调用的使用方法，包括其功能描述、语法、参数说明、返回值及示例。

---

## 1. `open` 系统调用

### 描述
`open` 系统调用用于打开一个文件，并返回一个文件描述符，用于后续对该文件的操作。

### 语法
```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
```

### 参数

- **`pathname`**: 要打开的文件的路径名。
- **`flags`**: 文件打开的选项，可以是下列值的组合：
  - `O_RDONLY`：以只读方式打开文件。
  - `O_WRONLY`：以只写方式打开文件。
  - `O_RDWR`：以读写方式打开文件。
  - `O_CREAT`：如果文件不存在则创建文件。需要与 `mode` 一起使用。
  - `O_EXCL`：与 `O_CREAT` 一起使用时，如果文件已存在，调用失败。
  - `O_TRUNC`：如果文件已存在并且以写方式打开，则长度截断为 0。
  - 其他标志请参考 `fcntl.h`。
- **`mode`**: 设置文件的权限（仅在使用 `O_CREAT` 时需要）。常用权限如 `0644`、`0755` 等。

### 返回值
- 成功：返回文件描述符（非负整数）。
- 失败：返回 `-1`，并设置 `errno` 以指示错误原因。

### 示例
```c
#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd = open("example.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    // 文件操作
    close(fd);
    return 0;
}
```

---

## 2. `openat` 系统调用

### 描述
`openat` 系统调用类似于 `open`，但它允许相对于一个已打开的目录文件描述符打开文件。提供了在多线程和相对路径操作中的更大灵活性和安全性。

### 语法
```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int openat(int dirfd, const char *pathname, int flags);
int openat(int dirfd, const char *pathname, int flags, mode_t mode);
```

### 参数

- **`dirfd`**: 目录文件描述符。如果 `pathname` 是绝对路径，则 `dirfd` 被忽略。可以使用特殊值 `AT_FDCWD` 表示当前工作目录。
- **`pathname`**: 要打开的文件的路径名。可以是相对路径，相对于 `dirfd` 指定的目录。
- **`flags`**: 与 `open` 中的 `flags` 参数相同。
- **`mode`**: 设置文件的权限（仅在使用 `O_CREAT` 时需要）。

### 返回值
- 成功：返回文件描述符（非负整数）。
- 失败：返回 `-1`，并设置 `errno` 以指示错误原因。

### 示例
```c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int dirfd = open("/tmp", O_RDONLY | O_DIRECTORY);
    if (dirfd == -1) {
        perror("open directory");
        return 1;
    }

    int fd = openat(dirfd, "example.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("openat");
        close(dirfd);
        return 1;
    }

    // 文件操作
    close(fd);
    close(dirfd);
    return 0;
}
```

---

## 3. `close` 系统调用

### 描述
`close` 系统调用用于关闭一个打开的文件描述符。关闭后，文件描述符将不再有效，资源也会被释放。

### 语法
```c
#include <unistd.h>

int close(int fd);
```

### 参数

- **`fd`**: 要关闭的文件描述符。

### 返回值
- 成功：返回 `0`。
- 失败：返回 `-1`，并设置 `errno` 以指示错误原因。

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

    // 文件操作

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}
```

---

## 注意事项

- **并发访问**：在多线程或多进程环境下使用 `openat` 可以减少路径解析的竞态条件。
- **权限管理**：使用 `open` 或 `openat` 创建文件时，确保正确设置 `mode`，以避免权限过宽导致的安全问题。
- **错误处理**：每次系统调用后，应检查返回值是否为 `-1`，并根据 `errno` 进行错误处理。

---
