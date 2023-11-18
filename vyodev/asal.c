#include <stdio.h>
#include <stdbool.h>

bool isPrimeRecursive(int num, int divisor) {
    if (num < 2) {
        return false;
    }

    if (divisor == 1) {
        return true;
    }

    if (num % divisor == 0) {
        return false;
    }

    return isPrimeRecursive(num, divisor - 1);
}

int main() {
    int num=8;
    bool value =isPrimeRecursive(num, num / 2);
    printf("%d",value);
    return 0;
}
