# `lseek` 系统调用文档

## 描述
`lseek` 系统调用用于移动文件描述符 `fd` 的读写位置。它允许在文件中任意位置进行读写操作。

## 语法
```c
#include <sys/types.h>
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence);
```

## 参数

- **`fd`**: 文件描述符，通常由 `open` 或相关系统调用返回。
- **`offset`**: 相对于 `whence` 的偏移量。
- **`whence`**: 指定偏移量的基准位置，可以是以下值之一：
  - `SEEK_SET`: 从文件开始位置设置偏移量。
  - `SEEK_CUR`: 从当前位置设置偏移量。
  - `SEEK_END`: 从文件末尾设置偏移量。

## 返回值

- **成功**：返回新的文件偏移量。
- **失败**：返回 `-1`，并设置 `errno` 以指示错误原因。

## 示例
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

    // 将文件偏移量设置到文件开头的第 10 个字节
    off_t new_offset = lseek(fd, 10, SEEK_SET);
    if (new_offset == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    printf("New offset: %ld\n", (long)new_offset);

    close(fd);
    return 0;
}
```

## 注意事项

- **超出文件范围**：`lseek` 可以将偏移量设置为超出文件末尾的位置，但不会改变文件大小。只有在写入时，文件大小才会增加。
- **错误处理**：每次调用后，应检查返回值是否为 `-1`，并根据 `errno` 进行错误处理。
- **无效操作**：对某些文件类型（如管道、套接字）调用 `lseek` 会失败，因为它们不支持文件偏移。

