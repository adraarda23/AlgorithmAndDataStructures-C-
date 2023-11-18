#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isPalindrome(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; ++i) {
        if (str[i] != str[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

int main() {
    char* palindromeStr = "radar";
    bool value =isPalindrome(palindromeStr);
    printf("%d",value);
    return 0;
}