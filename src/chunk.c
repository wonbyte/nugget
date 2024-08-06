#include "chunk.h"
#include "memory.h"
#include "value.h"
#include <stdint.h>
#include <stdlib.h>

void initChunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lines.lines = NULL;
    chunk->lines.counts = NULL;
    chunk->lines.capacity = 0;
    chunk->lines.count = 0;
    initValueArray(&chunk->constants);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code =
            GROW_ARRAY(uint8_t, chunk->code, (unsigned int)oldCapacity,
                       (unsigned int)chunk->capacity);
    }

    if (chunk->lines.capacity < chunk->lines.count + 1) {
        int oldLineCapacity = chunk->lines.capacity;
        chunk->lines.capacity = GROW_CAPACITY(oldLineCapacity);
        chunk->lines.lines =
            GROW_ARRAY(int, chunk->lines.lines, (unsigned int)oldLineCapacity,
                       (unsigned int)chunk->lines.capacity);
        chunk->lines.counts =
            GROW_ARRAY(int, chunk->lines.counts, (unsigned int)oldLineCapacity,
                       (unsigned int)chunk->lines.capacity);
    }

    if (chunk->lines.count > 0 &&
        chunk->lines.lines[chunk->lines.count - 1] == line) {
        chunk->lines.counts[chunk->lines.count - 1]++;
    } else {
        chunk->lines.lines[chunk->lines.count] = line;
        chunk->lines.counts[chunk->lines.count] = 1;
        chunk->lines.count++;
    }

    chunk->code[chunk->count] = byte;
    chunk->count++;
}

void freeChunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, (unsigned int)chunk->capacity);
    FREE_ARRAY(int, chunk->lines.lines, (unsigned int)chunk->lines.capacity);
    FREE_ARRAY(int, chunk->lines.counts, (unsigned int)chunk->lines.capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

int addConstant(Chunk* chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

int getLine(Chunk* chunk, int instructionIndex) {
    int accumulatedCount = 0;
    for (int i = 0; i < chunk->lines.count; i++) {
        accumulatedCount += chunk->lines.counts[i];
        if (instructionIndex < accumulatedCount) {
            return chunk->lines.lines[i];
        }
    }
    return -1; // Should never reach here if instructionIndex is valid
}
