#include <stdio.h>
#include <assert.h>
#include <string.h>

int anagram(char *s);
void char_count(char *s, int n, int *chars);

int main() {

    assert(anagram("aaabbb") == 3);
    assert(anagram("ab") == 1);
    assert(anagram("abc") == -1);
    assert(anagram("mnop") == 2);
    assert(anagram("xyyx") == 0);
    assert(anagram("xaxbbbxx") == 1);

    printf("Success\n");

    return 0;
}


int anagram(char *s) {
    size_t len = strlen(s);
    if (len % 2 != 0)
        return -1;

    int count1[26], count2[26];

    char_count(s, len / 2, count1);
    char_count(s + len / 2, len / 2, count2);

    int count = 0;

    for (int i = 0; i < 26; i += 1) {
        if (count1[i] > count2[i]) {
            count += count1[i] - count2[i];
        }
    }
    return count;
}

void char_count(char *s, int n, int chars[]) {
    memset(chars, 0, 26 * sizeof(*chars));
    for (int i = 0; i < n; i += 1)
        chars[s[i] - 'a'] += 1;
}
