#include <assert.h>
#include <stdio.h>

#include "value.h"

void test_initValueArray(void) {
    ValueArray array;
    initValueArray(&array);

    assert(array.count == 0);
    assert(array.capacity == 0);
    assert(array.values == NULL);

    freeValueArray(&array);
    printf("test_initValueArray passed.\n");
}

void test_writeValueArray(void) {
    ValueArray array;
    initValueArray(&array);

    writeValueArray(&array, 1.1);
    assert(array.count == 1);
    assert(array.capacity >= array.count);
    assert(array.values[0] == 1.1);

    writeValueArray(&array, 2.2);
    assert(array.count == 2);
    assert(array.capacity >= array.count);
    assert(array.values[1] == 2.2);

    freeValueArray(&array);
    printf("test_writeValueArray passed.\n");
}

void test_freeValueArray(void) {
    ValueArray array;
    initValueArray(&array);

    writeValueArray(&array, 1.1);
    writeValueArray(&array, 2.2);

    freeValueArray(&array);
    assert(array.count == 0);
    assert(array.capacity == 0);
    assert(array.values == NULL);

    printf("test_freeValueArray passed.\n");
}

int main(void) {
    test_initValueArray();
    test_writeValueArray();
    test_freeValueArray();
    printf("All ValueArray tests passed!\n");
    return 0;
}

