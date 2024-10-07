#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 1024

void add_large_numbers(const char *num1, const char *num2, char *result) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int carry = 0, sum = 0;
    int i = len1 - 1, j = len2 - 1, k = MAX_DIGITS - 1;

    result[k--] = '\0';

    while (i >= 0 || j >= 0 || carry) {
        int digit1 = (i >= 0) ? num1[i--] - '0' : 0;
        int digit2 = (j >= 0) ? num2[j--] - '0' : 0;
        sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result[k--] = (sum % 10) + '0';
    }

    memmove(result, result + k + 1, MAX_DIGITS - k - 1);
}

int main() {
    char num1[MAX_DIGITS], num2[MAX_DIGITS], result[MAX_DIGITS];
    while (scanf("%s %s", num1, num2) == 2) {
        add_large_numbers(num1, num2, result);
        printf("%s\n", result);
    }
    return 0;
}
