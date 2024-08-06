#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "memory.h"

void test_GROW_CAPACITY(void) {
    assert(GROW_CAPACITY(0) == 8);
    assert(GROW_CAPACITY(7) == 8);
    assert(GROW_CAPACITY(8) == 16);
    assert(GROW_CAPACITY(10) == 20);
    printf("test_GROW_CAPACITY passed.\n");
}

void test_reallocate(void) {
    // Test allocation
    int* array = (int*)reallocate(NULL, 0, sizeof(int) * 4);
    assert(array != NULL);

    // Test grow
    array = (int*)reallocate(array, sizeof(int) * 4, sizeof(int) * 8);
    assert(array != NULL);

    // Test shrink
    array = (int*)reallocate(array, sizeof(int) * 8, sizeof(int) * 4);
    assert(array != NULL);

    // Test free
    array = reallocate(array, sizeof(int) * 4, 0);
    assert(array == NULL);

    printf("test_reallocate passed.\n");
}

void test_GROW_ARRAY(void) {
    int* array = NULL;
    int oldCount = 0;
    int newCount = 8;

    // Test growing array
    array = GROW_ARRAY(int, array, oldCount, newCount);
    assert(array != NULL);

    // Initialize array values
    for (int i = 0; i < newCount; i++) {
        array[i] = i;
    }

    // Verify array values
    for (int i = 0; i < newCount; i++) {
        assert(array[i] == i);
    }

    // Test growing array again
    oldCount = newCount;
    newCount = 16;
    array = GROW_ARRAY(int, array, oldCount, newCount);
    assert(array != NULL);

    // Free array
    FREE_ARRAY(int, array, newCount);

    printf("test_GROW_ARRAY passed.\n");
}

void test_FREE_ARRAY(void) {
    int* array = (int*)reallocate(NULL, 0, sizeof(int) * 4);
    assert(array != NULL);

    FREE_ARRAY(int, array, 4);
    // TODO: Anything I can assert here?

    printf("test_FREE_ARRAY passed.\n");
}

int main(void) {
    test_GROW_CAPACITY();
    test_reallocate();
    test_GROW_ARRAY();
    test_FREE_ARRAY();

    printf("All memory tests passed!\n");

    return 0;
}
