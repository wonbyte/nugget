/**
 * @file chunk.h
 * @brief Header file defining the Chunk structure and related functions.
 */

#ifndef nugget_chunk_h
#define nugget_chunk_h

#include "common.h" // IWYU pragma: keep
#include "value.h"

/**
 * @enum OpCode
 * @brief Enum representing different operation codes (opcodes).
 *
 * This enum defines the various opcodes that the virtual machine can execute.
 */
typedef enum {
    OP_CONSTANT, /**< Produce a particular constant */
    OP_RETURN,   /**< Return from the current function */
} OpCode;

/**
 * @struct Chunk
 * @brief Structure representing a Chunk of bytecode.
 *
 * This structure holds a series of bytecode instructions for the virtual
 * machine, along with metadata about the capacity and usage of the bytecode
 * array.
 */
typedef struct {
    uint8_t* code;        /**< A series of instructions */
    ValueArray constants; /**< The constant pool for the array */
    int* lines;           /**< The line number of the offending source code */
    int capacity;         /**< The number of elements allocated */
    int count;            /**< The number of elements in use */
} Chunk;

/**
 * @brief Initialize a new Chunk.
 *
 * This function initializes a Chunk by setting its count and capacity to 0 and
 * its code pointer to NULL.
 *
 * @param chunk A pointer to the Chunk to initialize.
 */
void initChunk(Chunk* chunk);

/**
 * @brief Append a byte to the end of a Chunk.
 *
 * This function appends a byte to the end of a Chunk's code array. If the
 * Chunk's capacity is insufficient, it reallocates memory to accommodate the
 * new byte.
 *
 * @param chunk A pointer to the Chunk to append the byte to.
 * @param byte The byte to append to the chunk.
 * @param line The line number of the source code.
 */
void writeChunk(Chunk* chunk, uint8_t byte, int line);

/**
 * @brief Free the memory allocated for a Chunk.
 *
 * This function frees the memory allocated for the code array in the given
 * Chunk and resets its count and capacity to 0.
 *
 * @param chunk A pointer to the Chunk to free.
 */
void freeChunk(Chunk* chunk);

/**
 * @brief Add a new contant to the chunk.
 *
 * This function adds a new contant to the constant pool and then returns the
 * index where the constant was appended.
 *
 * @param chunk A pointer to the Chunk to append the constant to.
 * @param value The Value to add to the constant pool.
 * @return The index where the constant was appended.
 */
int addConstant(Chunk* chunk, Value value);

#endif // nugget_chunk_h
