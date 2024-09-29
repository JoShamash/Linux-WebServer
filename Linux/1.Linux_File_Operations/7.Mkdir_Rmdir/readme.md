# C 标准库函数：`mkdir` 和 `rmdir`

## `mkdir` 函数

### 概述

`mkdir` 函数用于创建一个新的目录。

### 函数原型

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int mkdir(const char *pathname, mode_t mode);
```

### 参数

- `pathname`：指向要创建的目录路径的指针。
- `mode`：新目录的权限设置，使用八进制表示。

### 返回值

- 成功时返回 `0`。
- 失败时返回 `-1`，并设置 `errno` 以指示错误。

### 示例

```c
#include <stdio.h>
#include <sys/stat.h>

int main() {
    if (mkdir("new_directory", 0755) == 0) {
        printf("Directory created successfully.\n");
    } else {
        perror("mkdir failed");
    }
    return 0;
}
```

## `rmdir` 函数

### 概述

`rmdir` 函数用于删除一个空目录。

### 函数原型

```c
#include <unistd.h>

int rmdir(const char *pathname);
```

### 参数

- `pathname`：指向要删除的目录路径的指针。

### 返回值

- 成功时返回 `0`。
- 失败时返回 `-1`，并设置 `errno` 以指示错误。

### 示例

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    if (rmdir("new_directory") == 0) {
        printf("Directory removed successfully.\n");
    } else {
        perror("rmdir failed");
    }
    return 0;
}
```

## 注意事项

- `mkdir` 创建的目录权限受当前 `umask` 值影响。
- `rmdir` 只能删除空目录。
- 错误处理对于确保程序的健壮性至关重要。

```

这个文档提供了 `mkdir` 和 `rmdir` 函数的基本用法和示例代码。希望对你有帮助！