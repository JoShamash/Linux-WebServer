# C 标准库函数：`getcwd` 和 `chdir`

## `getcwd` 函数

### 概述

`getcwd` 函数用于获取当前工作目录的绝对路径。

### 函数原型

```c
#include <unistd.h>

char *getcwd(char *buf, size_t size);
```

### 参数

- `buf`：指向存储路径的缓冲区。
- `size`：缓冲区的大小。

### 返回值

- 成功时返回 `buf`。
- 失败时返回 `NULL`，并设置 `errno` 以指示错误。

### 示例

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working directory: %s\n", cwd);
    } else {
        perror("getcwd failed");
    }
    return 0;
}
```

## `chdir` 函数

### 概述

`chdir` 函数用于更改当前工作目录。

### 函数原型

```c
#include <unistd.h>

int chdir(const char *path);
```

### 参数

- `path`：指向目标目录路径的指针。

### 返回值

- 成功时返回 `0`。
- 失败时返回 `-1`，并设置 `errno` 以指示错误。

### 示例

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    if (chdir("/path/to/directory") == 0) {
        printf("Directory changed successfully.\n");
    } else {
        perror("chdir failed");
    }
    return 0;
}
```

## 注意事项

- `getcwd` 的缓冲区大小应足够大以容纳路径。
- 使用 `chdir` 更改目录后，所有相对路径操作将基于新目录。
- 错误处理对于确保程序的健壮性至关重要。

```

这个文档提供了 `getcwd` 和 `chdir` 函数的基本用法和示例代码。希望对你有帮助！