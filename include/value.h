/**
 * @file value.h
 * @brief Definition of the Value type and ValueArray structure.
 */

#ifndef nugget_value_h
#define nugget_value_h

#include "common.h" // IWYU pragma: keep

/**
 * @typedef Value
 * @brief Represents a value in the Nugget virtual machine.
 *
 * This typedef abstracts how Nugget values are concretely represented in C.
 */
typedef double Value;

/**
 * @struct ValueArray
 * @brief A list of the values that appear as literals in the program.
 *
 * This structure represents a dynamic array of values (constant pool).
 */
typedef struct {
    int capacity;  /**< The total allocated capacity of the array. */
    int count;     /**< The current number of elements in the array. */
    Value* values; /**< A pointer to the array of values. */
} ValueArray;

/**
 * @brief Initializes a ValueArray.
 *
 * This function initializes a ValueArray, setting its initial capacity and
 * count to zero and its values pointer to NULL.
 *
 * @param array A pointer to the ValueArray to initialize.
 */
void initValueArray(ValueArray* array);

/**
 * @brief Appends a Value to a ValueArray.
 *
 * This function appends a given Value to the end of a ValueArray. If the
 * array's capacity is insufficient, it is increased to accommodate the new
 * value.
 *
 * @param array A pointer to the ValueArray to append to.
 * @param value The Value to append.
 */
void writeValueArray(ValueArray* array, Value value);

/**
 * @brief Frees the memory allocated for a ValueArray.
 *
 * This function frees the memory allocated for the values in a ValueArray and
 * resets its capacity and count to zero.
 *
 * @param array A pointer to the ValueArray to free.
 */
void freeValueArray(ValueArray* array);

/**
 * @brief Print a Value.
 *
 * This is a convenient function to print a Value in nugget.
 *
 * @param value The Value to print.
 */
void printValue(Value value);

#endif // nugget_value_h
