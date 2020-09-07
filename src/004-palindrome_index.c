#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

int palindromeIndex(char *s);
bool isPalindrome(char *s, int start, int end);


int main() {
    assert(palindromeIndex("aaab") == 3);
    assert(palindromeIndex("baa") == 0);
    assert(palindromeIndex("aaa") == -1);

    printf("Success!");
    return 0;
}

bool isPalindrome(char *s, int start, int end) {
    while (start < end)
        if (s[start++] != s[end--])
            return false;
    return true;
}


int palindromeIndex(char *s) {
    size_t start = 0, end = strlen(s) - 1;
    size_t c = -1;

    while (start < end) {
        if (s[start] != s[end]) {
            if (c != -1) return -1;

            if (isPalindrome(s, start + 1, end)) {
                return start;
            } else if (isPalindrome(s, start, end - 1)) {
                return end;
            } else {
                return -1;
            }
        }

        start += 1;
        end   -= 1;
    }

    return c;
}


