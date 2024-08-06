#include <assert.h>
#include <stdio.h>

#include "chunk.h"

void test_initChunk(void) {
    Chunk chunk;
    initChunk(&chunk);

    assert(chunk.count == 0);
    assert(chunk.capacity == 0);
    assert(chunk.code == NULL);
    assert(chunk.lines == NULL);
    assert(chunk.constants.count == 0);
    assert(chunk.constants.capacity == 0);
    assert(chunk.constants.values == NULL);

    freeChunk(&chunk);
    printf("test_initChunk passed.\n");
}

void test_writeChunk(void) {
    Chunk chunk;
    initChunk(&chunk);

    writeChunk(&chunk, 0x01, 10);
    assert(chunk.count == 1);
    assert(chunk.capacity >= chunk.count);
    assert(chunk.code[0] == 0x01);
    assert(chunk.lines[0] == 10);

    writeChunk(&chunk, 0x02, 20);
    assert(chunk.count == 2);
    assert(chunk.capacity >= chunk.count);
    assert(chunk.code[1] == 0x02);
    assert(chunk.lines[1] == 20);

    freeChunk(&chunk);
    printf("test_writeChunk passed.\n");
}

void test_freeChunk(void) {
    Chunk chunk;
    initChunk(&chunk);

    writeChunk(&chunk, 0x01, 10);
    writeChunk(&chunk, 0x02, 20);

    freeChunk(&chunk);
    assert(chunk.count == 0);
    assert(chunk.capacity == 0);
    assert(chunk.code == NULL);
    assert(chunk.lines == NULL);
    assert(chunk.constants.count == 0);
    assert(chunk.constants.capacity == 0);
    assert(chunk.constants.values == NULL);

    printf("test_freeChunk passed.\n");
}

void test_addConstant(void) {
    Chunk chunk;
    initChunk(&chunk);

    int index = addConstant(&chunk, 1.1);
    assert(index == 0);
    assert(chunk.constants.count == 1);
    assert(chunk.constants.values[0] == 1.1);

    index = addConstant(&chunk, 2.2);
    assert(index == 1);
    assert(chunk.constants.count == 2);
    assert(chunk.constants.values[1] == 2.2);

    freeChunk(&chunk);
    printf("test_addConstant passed.\n");
}

int main(void) {
    test_initChunk();
    test_writeChunk();
    test_freeChunk();
    test_addConstant();

    printf("All Chunk tests passed!\n");

    return 0;
}
