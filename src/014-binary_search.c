#include <stdio.h>
#include <assert.h>

int custom_sqrt(int n);
int sqrt_recursive(int n, int min, int max);

int main() {
    assert(custom_sqrt(25) == 5);
    assert(custom_sqrt(7056) == 84);

    printf("Success!");
    return 0;
}

int custom_sqrt(int n) {
    return sqrt_recursive(n, 0, n);
}

int sqrt_recursive(int n, int min, int max) {
    int mid = (min + max) / 2;
    int squared = mid * mid;
    if (squared == n)
        return mid;
    else if (squared > n)
        return sqrt_recursive(n, min, mid);
    else
        return sqrt_recursive(n, mid, max);
}
