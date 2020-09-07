#include <stdio.h>
#include <assert.h>

int even_fibonacci(int n) {
    int a = 1, b = 1, sum = 0;
    while (b < n) {
        if (b % 2 == 0) sum += b;
        int t = a;
        a = b;
        b += t;
    }
    return sum;
}

int main() {
    assert(even_fibonacci(10) == 10);
    assert(even_fibonacci(100) == 44);
    printf("Success!");

    return 0;
}
