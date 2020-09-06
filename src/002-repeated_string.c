#include <stdio.h>
#include <assert.h>
#include <string.h>

long repeated_string(char *s, long n);
size_t charncount(char *s, size_t n, char c);

int main() {
    assert(repeated_string("a", 1000000000000) == 1000000000000);
    assert(repeated_string("aba", 10) == 7);

    printf("Success");
    return 0;
}

long repeated_string(char *s, long n) {
    size_t len         = strlen(s);
    size_t start_count = charncount(s, len, 'a');
    size_t end_count   = charncount(s, n % len, 'a');
    return start_count * (n / len) + end_count;
}

size_t charncount(char *s, size_t n, char c) {
    size_t count = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == c)
            count += 1;
    }
    return count;
}
