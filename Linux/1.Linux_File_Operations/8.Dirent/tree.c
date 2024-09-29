#include "header.h"

static int tabs = 0; // 制表符个数
static int dir_sum = 0; // 目录个数
static int file_sum = 0; // 文件个数


void print_filename(const char *path, bool isLast, bool father_last){ // 格式化打印文件名
    if(father_last){
        for(int i = 0; i < tabs; i++)    
            printf("%s", BLANK);
    }else{
        for(int i = 0; i < tabs; i++)
            printf("%s", TAB);
    }

    if(isLast)
        printf("%s%s\n", LASTARROW, path);        
    else
        printf("%s%s\n", ARROW, path);
}

int tree(const char *path, bool father_last){ // 实现tree命令
    // 先读取所有目录项
    struct dirent** namelist;
    int n = scandir(path, &namelist, NULL, alphasort);
    if (n < 0) {
        perror("scandir()");
        return -1;
    }

    for (int i = 0; i < n; i++) {
        struct dirent* pdirent = namelist[i];
        if(strcmp(pdirent->d_name, ".") == 0 || strcmp(pdirent->d_name, "..") == 0) {
            free(namelist[i]);
            continue;
        }

        if(pdirent->d_type != DT_DIR) file_sum++;

        bool isLast = (i == n - 1);
        bool isDir = (pdirent->d_type == DT_DIR);

        // 打印文件名/子目录名
        print_filename(pdirent->d_name, isLast, father_last);

        // 是目录类型，递归调用
        if(isDir){
            // 生成新路径
            char newpath[1024];
            sprintf(newpath, "%s/%s", path, pdirent->d_name);
            
            bool father_last_is_dir = isLast; //父目录为父目录的目录流中最后一个目录

            dir_sum++;
            tabs++;
            tree(newpath, father_last_is_dir);
        }

        free(namelist[i]);
    }
    free(namelist);

    tabs--;

    return 0;
}

int main(int argc, char *argv[]) // 实现 tree -a [filename] 的效果
{
    ARGS_CHECK(argc, 2);
    puts(argv[1]);
    tree(argv[1], false);

    printf("\n%d directories, %d files\n", dir_sum, file_sum);
    return 0;
}