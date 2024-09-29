# Linux 系统调用：`chmod` 和 `chown`

## `chmod` 系统调用

### 概述

`chmod` 系统调用用于更改文件或目录的权限。

### 函数原型

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int chmod(const char *path, mode_t mode);
```

### 参数

- `path`：指向文件或目录路径的指针。
- `mode`：新的权限设置，使用八进制表示。

### 返回值

- 成功时返回 `0`。
- 失败时返回 `-1`，并设置 `errno` 以指示错误。

### 示例

```c
#include <stdio.h>
#include <sys/stat.h>

int main() {
    if (chmod("example.txt", 0644) == -1) {
        perror("chmod failed");
        return 1;
    }
    return 0;
}
```

## `chown` 系统调用

### 概述

`chown` 系统调用用于更改文件或目录的所有者和所属组。

### 函数原型

```c
#include <unistd.h>
#include <sys/types.h>

int chown(const char *path, uid_t owner, gid_t group);
```

### 参数

- `path`：指向文件或目录路径的指针。
- `owner`：新的所有者的用户 ID。
- `group`：新的所属组的组 ID。

### 返回值

- 成功时返回 `0`。
- 失败时返回 `-1`，并设置 `errno` 以指示错误。

### 示例

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    if (chown("example.txt", 1000, 1000) == -1) {
        perror("chown failed");
        return 1;
    }
    return 0;
}
```

## 注意事项

- 使用这些系统调用需要适当的权限。
- 错误处理对于确保程序的健壮性至关重要。

```

这个文档提供了 `chmod` 和 `chown` 系统调用的基本用法和示例代码。希望对你有帮助！