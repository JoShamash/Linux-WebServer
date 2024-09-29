# C 标准库函数：目录操作

## `opendir` 函数

### 概述

`opendir` 函数用于打开一个目录流，以便读取目录项。

### 函数原型

```c
#include <dirent.h>

DIR *opendir(const char *name);
```

### 参数

- `name`：指向要打开的目录路径的指针。

### 返回值

- 成功时返回指向 `DIR` 结构的指针。
- 失败时返回 `NULL`，并设置 `errno` 以指示错误。

### 示例

```c
DIR *dir = opendir("/path/to/directory");
if (dir == NULL) {
    perror("opendir failed");
}
```

## `readdir` 函数

### 概述

`readdir` 函数用于读取目录流中的一个目录项。

### 函数原型

```c
#include <dirent.h>

struct dirent *readdir(DIR *dir);
```

### 参数

- `dir`：指向已打开的目录流的指针。

### 返回值

- 成功时返回指向 `dirent` 结构的指针。
- 读取到目录末尾或出错时返回 `NULL`。

### 示例

```c
struct dirent *entry;
while ((entry = readdir(dir)) != NULL) {
    printf("Directory entry: %s\n", entry->d_name);
}
```

## `closedir` 函数

### 概述

`closedir` 函数用于关闭目录流。

### 函数原型

```c
#include <dirent.h>

int closedir(DIR *dir);
```

### 参数

- `dir`：指向要关闭的目录流的指针。

### 返回值

- 成功时返回 `0`。
- 失败时返回 `-1`，并设置 `errno` 以指示错误。

### 示例

```c
if (closedir(dir) == -1) {
    perror("closedir failed");
}
```

## `telldir` 函数

### 概述

`telldir` 函数返回目录流当前的读取位置。

### 函数原型

```c
#include <dirent.h>

off_t telldir(DIR *dir);
```

### 参数

- `dir`：指向已打开的目录流的指针。

### 返回值

- 返回当前读取位置的偏移量。

### 示例

```c
off_t position = telldir(dir);
```

## `seekdir` 函数

### 概述

`seekdir` 函数用于设置目录流的读取位置。

### 函数原型

```c
#include <dirent.h>

void seekdir(DIR *dir, off_t offset);
```

### 参数

- `dir`：指向已打开的目录流的指针。
- `offset`：要设置的偏移量。

### 示例

```c
seekdir(dir, position);
```

## `rewinddir` 函数

### 概述

`rewinddir` 函数用于将目录流重新定位到目录的开头。

### 函数原型

```c
#include <dirent.h>

void rewinddir(DIR *dir);
```

### 参数

- `dir`：指向已打开的目录流的指针。

### 示例

```c
rewinddir(dir);
```

## 注意事项

- 确保在使用完目录流后调用 `closedir` 以释放资源。
- 错误处理对于确保程序的健壮性至关重要。

```

这个文档提供了目录操作函数的基本用法和示例代码。希望对你有帮助！