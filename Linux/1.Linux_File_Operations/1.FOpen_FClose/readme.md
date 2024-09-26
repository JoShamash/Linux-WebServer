# 文件流操作指南

本文档介绍了 C 语言中常用的文件流操作函数、打开模式以及数据读写方法。

---

## 文件流打开与关闭

### 函数原型

```c
FILE* fopen(const char* path, const char* mode); // 打开文件，参数为文件路径和模式
int fclose(FILE* stream);                        // 关闭文件流
```

### 打开模式说明

| 模式  | 读 (Read) | 写 (Write) | 位置 (Position) | 截断原内容 (Truncate) | 创建 (Create) |
|-------|-----------|------------|------------------|------------------------|----------------|
| `rb`  | Y         | N          | 文件头           | N                      | N              |
| `rb+` | Y         | Y          | 文件头           | N                      | N              |
| `wb`  | N         | Y          | 文件头           | Y                      | Y              |
| `wb+` | Y         | Y          | 文件头           | Y                      | Y              |
| `ab`  | N         | Y          | 文件尾           | N                      | Y              |
| `ab+` | Y         | Y          | 文件尾           | N                      | Y              |

### 模式详细说明

- **文本模式**
  - `"r"`：以只读模式打开文件。文件必须存在。
  - `"w"`：以写入模式打开文件。如果文件不存在则创建，存在则清空内容。
  - `"a"`：以追加模式打开文件。如果文件不存在则创建，写入数据会追加到文件末尾。
  - `"r+"`：以读写模式打开文件。文件必须存在。
  - `"w+"`：以读写模式打开文件。如果文件不存在则创建，存在则清空内容。
  - `"a+"`：以读写模式打开文件。如果文件不存在则创建，写入数据会追加到文件末尾。

- **二进制模式**
  - `"rb"`：以二进制模式只读打开文件。文件必须存在。
  - `"wb"`：以二进制模式写入打开文件。如果文件不存在则创建，存在则清空内容。
  - `"ab"`：以二进制模式追加打开文件。如果文件不存在则创建。
  - `"rb+"`：以二进制模式读写打开文件。文件必须存在。
  - `"wb+"`：以二进制模式读写打开文件。如果文件不存在则创建，存在则清空内容。
  - `"ab+"`：以二进制模式读写打开文件。如果文件不存在则创建，写入数据会追加到文件末尾。

---

## 数据块读写

### 函数原型

```c
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
```

### 功能说明

- **`fread`**：从文件流 `stream` 中读取 `nmemb` 个元素，每个元素的大小为 `size` 字节，写入到 `ptr` 指向的内存中。
- **`fwrite`**：从 `ptr` 指向的内存中读取 `nmemb` 个元素，每个元素的大小为 `size` 字节，写入到文件流 `stream` 中。

---

## 格式化读写

### 函数原型

```c
int printf(const char *format, ...);                  // 相当于 fprintf(stdout, format, ...);
int scanf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);
int fscanf(FILE *stream, const char *format, ...);
int sprintf(char *str, const char *format, ...);       // eg: sprintf(buf, "The string is: %s", str);
int sscanf(const char *str, const char *format, ...);
int snprintf(char *str, size_t size, const char *format, ...); // 安全的 sprintf 版本
```

### 功能说明

- **`fprintf`**：将格式化后的字符串写入到文件流 `stream` 中。
- **`sprintf`**：将格式化后的字符串写入到字符串 `str` 中。
- **`printf`** 和 **`scanf`**：分别用于标准输出和标准输入的格式化操作，等同于 `fprintf(stdout, ...)` 和 `fscanf(stdin, ...)`。

---

## 单个字符读写

### 函数原型

```c
int fgetc(FILE *stream);
int fputc(int c, FILE *stream);
int getc(FILE *stream);        // 等同于 fgetc(FILE* stream)
int putc(int c, FILE *stream); // 等同于 fputc(int c, FILE* stream)
int getchar(void);             // 等同于 fgetc(stdin)
int putchar(int c);            // 等同于 fputc(int c, stdout)
```

### 功能说明

- **`getchar`** 和 **`putchar`**：从标准输入流读取字符和向标准输出流写入字符。
- **`fgetc`**、**`fputc`**、**`getc`**、**`putc`**：从文件流 `stream` 中读取和写入字符。

---

## 字符串读写

### 函数原型

```c
char *fgets(char *s, int size, FILE *stream);
int fputs(const char *s, FILE *stream);
int puts(const char *s);           // 等同于 fputs(const char *s, stdout)
char *gets(char *s);               // 等同于 fgets(s, INT_MAX, stdin) （已弃用）
```

### 功能说明

- **`fgets`** 和 **`fputs`**：
  - 用于从文件流 `stream` 中读取和写入一行数据。
  - `fgets` 可以指定目标缓冲区的大小，较 `gets` 更安全；当读取的行字符数超过 `size` 时，`fgets` 会在下一次调用时继续读取剩余的字符，并保留行尾的换行符。
  - `fputs` 不会在行尾自动添加换行符。

- **`puts`** 和 **`gets`**：
  - 用于从标准输入输出流中读取和写入一行数据。
  - `puts` 会在输出字符串后自动添加一个换行符。
  - `gets` 已在新版标准库中弃用，建议使用 `fgets` 代替。

---

## 注意事项

- **安全性**：避免使用 `gets`，因为它不限制输入长度，容易导致缓冲区溢出。推荐使用 `fgets` 来替代 `gets`。
- **换行符处理**：`fgets` 会保留行尾的换行符，`fputs` 不会自动添加换行符，而 `puts` 会自动添加一个换行符。
- **文件模式选择**：根据具体需求选择合适的文件打开模式，特别是在处理二进制文件时需要使用相应的二进制模式（如 `rb`, `wb` 等）。


---

## 文件定位

文件定位用于读取或设置文件的当前读写点。所有通过文件指针进行的读写操作，都是从当前读写点开始的。常用的文件定位函数包括：

### 常用函数

- **`fseek`**：设置当前读写点到偏移 `whence` 长度为 `offset` 处。
  - `SEEK_SET`：文件开头
  - `SEEK_CUR`：文件当前位置
  - `SEEK_END`：文件末尾

- **`ftell`**：获取当前的读写点。

- **`rewind`**：将文件当前读写点移动到文件头，相当于 `fseek(fp, 0, SEEK_SET)`。

### 函数原型

```c
#include <stdio.h>

int fseek(FILE *stream, long offset, int whence);
long ftell(FILE *stream);
void rewind(FILE *stream);
```

### 示例代码

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("example.txt", "r");
    if (fp == NULL) {
        perror("Failed to open file");
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    printf("File size: %ld bytes\n", size);

    rewind(fp);
    // 继续进行文件操作...

    fclose(fp);
    return 0;
}
```

---

## 文本文件和二进制文件

### 文本文件

- **定义**：文本文件包含一串 ASCII 字符序列。
- **操作**：使用 `fread` 读取到内存时，应分配字符串类型的内存区域。若需将文件内容转换为特定数据类型，使用 `fscanf`。

### 二进制文件

- **定义**：二进制文件是内存数据块按字节直接存储的文件。
- **操作**：只能使用 `fread` 和 `fwrite` 进行读写操作。读写时需遵循“写入是什么类型，读取就使用同样的类型”的原则。

### 示例代码

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *fp = fopen("file1", "r+");
    if (fp == NULL) {
        perror("Failed to open file");
        return 1;
    }

    // 从文本内容读到字符串数据
    char buf[1024] = {0};
    fread(buf, 1, 1024, fp);
    printf("buf = %s\n", buf);

    // 从文本内容读到 int 数据
    fseek(fp, 0, SEEK_SET);
    int i;
    fscanf(fp, "%d", &i);
    printf("i = %d\n", i);

    fclose(fp);
    return 0;
}
```

---

## 注意事项

- **文件类型选择**：根据文件内容选择合适的操作方法，文本文件适合使用格式化输入输出函数，而二进制文件则使用数据块读写函数。
- **文件定位**：在进行文件读写操作前，确保正确设置文件的读写位置，以避免读写错误。

---

## 示例代码

### 打开文件并读取内容

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return 0;
}
```

### 写入数据到文件

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    fprintf(file, "Hello, World!\n");
    fclose(file);
    return 0;
}
```

---

以上内容涵盖了 C 语言中文件流操作的基本用法和注意事项，帮助更高效地进行文件读写操作。