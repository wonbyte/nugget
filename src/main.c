#include "chunk.h"
#include "common.h" // IWYU pragma: keep
#include "debug.h"

int main(int argc __attribute__((unused)),
         const char* argv[] __attribute__((unused))) {
    Chunk chunk;
    initChunk(&chunk);

    int constant = addConstant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT);
    writeChunk(&chunk, (uint8_t)constant);

    writeChunk(&chunk, OP_RETURN);

    disassembleChunk(&chunk, "test chunk");

    freeChunk(&chunk);
    return 0;
}
