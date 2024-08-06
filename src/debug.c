#include <stdio.h>

#include "chunk.h"
#include "common.h" // IWYU pragma: keep
#include "debug.h"
#include "value.h"

/**
 * @brief Prints the name of an instruction and returns the next offset.
 *
 * This function prints the name of a simple instruction.
 * It then returns the offset of the next instruction in the chunk's code array.
 *
 * @param name A string representing the name of the instruction.
 * @param offset The current offset of the instruction within the chunk's code
 * array.
 * @return The offset of the next instruction in the chunk's code array.
 */
static int simpleInstruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

/**
 * @brief Prints the name and details of a constant instruction and returns the
 * next offset.
 *
 * This function prints the name and details of a constant instruction. It
 * retrieves the constant index from the chunk's code array, prints the constant
 * value, and then returns the offset of the next instruction in the chunk's
 * code array.
 *
 * @param name A string representing the name of the instruction.
 * @param chunk A pointer to the Chunk containing the instruction.
 * @param offset The current offset of the instruction within the chunk's code
 * array.
 * @return The offset of the next instruction in the chunk's code array.
 */
static int constantInstruction(const char* name, Chunk* chunk, int offset) {
    uint8_t constant = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");
    return offset + 2;
}

int disassembleInstruction(Chunk* chunk, int offset) {
    printf("%04d ", offset);

    int currentLine = getLine(chunk, offset);
    if (offset > 0 && currentLine == getLine(chunk, offset - 1)) {
        printf("   | ");
    } else {
        printf("%4d ", currentLine);
    }

    uint8_t instruction = chunk->code[offset];
    switch (instruction) {
    case OP_CONSTANT: return constantInstruction("OP_CONSTANT", chunk, offset);
    case OP_RETURN: return simpleInstruction("OP_RETURN", offset);
    default: printf("Unknown opcode %d\n", instruction); return offset + 1;
    }
}

void disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);

    for (int offset = 0; offset < chunk->count;) {
        offset = disassembleInstruction(chunk, offset);
    }
}
