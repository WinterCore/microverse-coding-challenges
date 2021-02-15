#include <stdio.h>

#include "../minunit.h"
#include "linked-list.h"

int tests_run = 0;

static char *should_get_node_value_after_2_adds() {
    struct Node *node = NULL;
    ll_add(&node, 3);
    ll_add(&node, 5);
    mu_assert("ERROR: Get node value after 2 adds", ll_get(&node, 1) == 5);
    return 0;
}

static char *should_get_first_node_value() {
    struct Node *node = NULL;
    ll_add(&node, 3);
    mu_assert("ERROR: Get first node value", ll_get(&node, 0) == 3);
    return 0;
}

static char *should_work_with_multiple_adds_and_gets() {
    struct Node *node = NULL;
    ll_add(&node, 3);
    ll_add(&node, 5);
    ll_add(&node, 7);
    ll_add(&node, 1);
    ll_add(&node, 4);
    char *error = "ERROR: Multiple adds and gets";

    mu_assert(error, ll_get(&node, 0) == 3);
    mu_assert(error, ll_get(&node, 1) == 5);
    mu_assert(error, ll_get(&node, 2) == 7);
    mu_assert(error, ll_get(&node, 3) == 1);
    mu_assert(error, ll_get(&node, 4) == 4);
    return 0;
}

static char *all_tests() {
    mu_run_test(should_get_node_value_after_2_adds);
    mu_run_test(should_get_first_node_value);
    mu_run_test(should_work_with_multiple_adds_and_gets);
    return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != NULL) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != NULL;
}
