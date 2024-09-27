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
#inc