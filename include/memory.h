/**
 * @file memory.h
 * @brief Memory management macros and functions.
 */

#ifndef nugget_memory_h
#define nugget_memory_h

#include "common.h" // IWYU pragma: keep

/**
 * @brief Macro to calculate the new capacity for dynamic arrays.
 *
 * This macro calculates the new capacity for a dynamic array, ensuring it is at
 * least 8 and otherwise doubling the current capacity.
 *
 * @param capacity The current capacity of the array.
 * @return The new capacity of the array.
 */
#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)

/**
 * @brief Macro to grow a dynamic array.
 *
 * This macro reallocates memory for a dynamic array to a new size, given the
 * type of the array, the current pointer to the array, the old count of
 * elements, and the new count of elements.
 *
 * @param type The type of the elements in the array.
 * @param pointer The current pointer to the array.
 * @param oldCount The current number of elements in the array.
 * @param newCount The new number of elements in the array.
 * @return A pointer to the newly allocated memory for the array.
 */
#define GROW_ARRAY(type, pointer, oldCount, newCount)                          \
    (type*)reallocate(pointer, sizeof(type) * (oldCount),                      \
                      sizeof(type) * (newCount))

/**
 * @brief Free an array of elements.
 *
 * This macro frees an array of elements by reallocating the memory with a new
 * size of 0. It effectively deallocates the memory previously allocated for the
 * array.
 *
 * @param type The type of the elements in the array.
 * @param pointer The pointer to the array to be freed.
 * @param oldCount The number of elements in the array.
 */
#define FREE_ARRAY(type, pointer, oldCount)                                    \
    reallocate(pointer, sizeof(type) * (oldCount), 0)

/**
 * @brief Reallocate memory for a given pointer.
 *
 * This function reallocates memory for a given pointer from the old size to the
 * new size. If the new size is zero, the memory is freed. If the pointer is
 * null, it allocates new memory.
 *
 * @param pointer The pointer to the memory to be reallocated.
 * @param oldSize The old size of the memory block.
 * @param newSize The new size of the memory block.
 * @return A pointer to the newly allocated memory, or NULL if the allocation
 * fails.
 */
void* reallocate(void* pointer, size_t oldSize, size_t newSize);

#endif // nugget_memory_h
