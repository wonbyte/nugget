/**
 * @file debug.h
 * @brief Debugging functions for disassembling bytecode.
 */

#ifndef nugget_debug_h
#define nugget_debug_h

#include "chunk.h"

/**
 * @brief Disassembles the instructions in a Chunk.
 *
 * This function disassembles and prints the instructions contained in the given
 * Chunk. It provides a human-readable representation of the bytecode, which is
 * useful for debugging and understanding the Chunk's contents.
 *
 * @param chunk A pointer to the Chunk structure to disassemble.
 * @param name A string representing the name of the Chunk, used as a header in
 * the disassembly output.
 */
void disassembleChunk(Chunk* chunk, const char* name);

/**
 * @brief Disassembles a single instruction in a Chunk.
 *
 * This function disassembles and prints a single instruction from the given
 * Chunk at the specified offset. It returns the offset of the next instruction,
 * which is useful for iterating through the Chunk.
 *
 * @param chunk A pointer to the Chunk structure containing the instruction.
 * @param offset The offset of the instruction to disassemble within the Chunk's
 * code array.
 * @return The offset of the next instruction in the Chunk.
 */
void dissassembleInstruction(Chunk* chunk, int offset);

#endif // nugget_debug_h
