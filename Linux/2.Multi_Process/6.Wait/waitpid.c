#include "../header.h"

int main() {
    int status;
    int child_count = 3; // 子进程数量

    for (int i = 0; i < child_count; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // 子进程执行的代码
            while (1) {
                sleep(1);
                printf("I am child %d\n", getpid());
            }
        }
    }

    // 父进程等待所有子进程退出
    int exited_children = 0;
    while (exited_children < child_count) {
        pid_t wait_pid = waitpid(-1, &status, 0);
        if (wait_pid > 0) {
            if (WIFEXITED(status)) {
                printf("child(%d) exit code = %d\n", wait_pid, WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("child(%d) crash, signal = %d\n", wait_pid, WTERMSIG(status));
            }
            exited_children++;
        }
    }

    printf("All children have exited. Parent exiting.\n");
    return 0;
}
