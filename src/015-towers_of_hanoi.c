#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

char *hanoi_steps(int disks);
void move(int start, int inter, int dest, int discs, char *str);

int main() {
    assert(strcmp(hanoi_steps(2), "1->2 1->3 2->3") == 0);
    assert(strcmp(hanoi_steps(3), "1->3 1->2 3->2 1->3 2->1 2->3 1->3") == 0);
    assert(strcmp(hanoi_steps(4), "1->2 1->3 2->3 1->2 3->1 3->2 1->2 1->3 2->3 2->1 3->1 2->3 1->2 1->3 2->3") == 0);

    printf("Success!");
    return 0;
}


char *hanoi_steps(int discs) {
    int size = (pow(2, discs) - 1) * 5;
    char *str = malloc(size);
    str[0] = '\0';
    move(1, 2, 3, discs, str);
    str[size - 1] = '\0';
    return str;
}

void move(int start, int inter, int dest, int discs, char *str) {
    char temp[5];
    if (discs == 1) {
        sprintf(temp, "%d->%d", start, dest);
        strcat(str, temp);
    } else {
        move(start, dest, inter, discs - 1, str);
        strcat(str, " ");
        move(start, inter, dest, 1, str);
        strcat(str, " ");
        move(inter, start, dest, discs - 1, str);
    }
}

