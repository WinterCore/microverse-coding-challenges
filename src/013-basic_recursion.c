#include <stdio.h>
#include <assert.h>

int sum(int n);

int main() {
    assert(sum(4) == 10);
    assert(sum(10) == 55);

    printf("Success!");
    return 0;
}


int sum(int n) {
    return n < 2 ? n : n + sum(n - 1);
}
