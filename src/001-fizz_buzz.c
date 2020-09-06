#include <stdio.h>

#define N 20

void fizzbuzz(int n);

int main() {
    for (int i = 0; i < N; i += 1) {
        fizzbuzz(i);
        printf("\n");
    }

    return 0;
}



void fizzbuzz(int n) {
    if (n % 3 == 0 && n % 5 == 0) printf("FizzBuzz");
    else if (n % 3 == 0) printf("Fizz");
    else if (n % 5 == 0) printf("Buzz");
    else printf("%d", n);
}
