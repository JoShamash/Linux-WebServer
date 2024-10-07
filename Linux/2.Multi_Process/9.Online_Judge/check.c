#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

// 使用 popen 运行程序并获取输出
int get_program_output(const char *program, const char *input_file, char *output_buffer, size_t buffer_size) {
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "%s < %s", program, input_file);

    FILE *pipe = popen(command, "r");
    if (!pipe) {
        perror("popen failed");
        return -1;
    }

    size_t total_read = 0;
    while (fgets(output_buffer + total_read, buffer_size - total_read, pipe) != NULL) {
        total_read = strlen(output_buffer);
        if (total_read >= buffer_size - 1) {
            break; // 防止缓冲区溢出
        }
    }

    pclose(pipe);
    return 0;
}

// 比较输出
int compare_output(const char *student_output, const char *standard_output) {
    return strcmp(student_output, standard_output) == 0;
}

int main() {
    char standard_output[BUFFER_SIZE] = {0};
    char student_output[BUFFER_SIZE] = {0};

    // 获取标准答案程序的输出
    if (get_program_output("./standard_answer_program", "input.txt", standard_output, sizeof(standard_output)) != 0) {
        fprintf(stderr, "Failed to get standard answer program output\n");
        return 1;
    } else {
        printf("Standard output:\n%s", standard_output);
        printf("standard.exe complete\n\n");
    }

    // 获取考生程序的输出
    if (get_program_output("./student_program", "input.txt", student_output, sizeof(student_output)) != 0) {
        fprintf(stderr, "Failed to get student program output\n");
        return 1;
    } else {
        printf("Student output:\n%s", student_output);
        printf("student.exe complete\n");
    }

    // 比较输出
    if (compare_output(student_output, standard_output)) {
        printf("Output is correct!\n");
    } else {
        printf("Output is incorrect.\n");
    }

    return 0;
}
