// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void *malloc(size_t size)
{
	void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	mem_list_add (ptr, size);

    return ptr;
}

void *calloc(size_t nmemb, size_t size)
{
	size_t total_size = nmemb * size;

    // Check for overflow in multiplication
    if (nmemb != 0 && total_size / nmemb != size) {
        return NULL;  // Return NULL on overflow
    }

    // Allocate memory using malloc
    void *ptr = malloc(total_size);
    if (!ptr) {
        return NULL;  // Return NULL if allocation fails
    }

    // Initialize allocated memory to zero
    memset(ptr, 0, total_size);

    return ptr;
}

void free(void *ptr)
{
	struct mem_list *ni = mem_list_find(ptr);

	munmap(ni->start, ni->len);

	mem_list_del(ni->start);
}

void *realloc(void *ptr, size_t size)
{
	if (ptr == NULL) {
        return malloc(size);
    }

    // Step 2: If size is 0, free the memory and return NULL
    if (size == 0) {
        free(ptr);
        return NULL;
    }

    // Step 3: Attempt to resize the memory block with mremap
    void *new_ptr = mremap(ptr, 0, size, MREMAP_MAYMOVE);
    if (new_ptr == MAP_FAILED) {
        // mremap failed, fall back to malloc and memcpy
        new_ptr = malloc(size);
        if (new_ptr) {
            // Copy old data to new memory and free the old memory
            memcpy(new_ptr, ptr, size); // Assumes size <= original size
            free(ptr);
        }
    }

    return new_ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    if (nmemb && size > (size_t)-1 / nmemb) {
        errno = ENOMEM;
        return NULL; // Overflow detected
    }

    size_t total_size = nmemb * size;

    // Step 2: Handle the case where ptr is NULL, act like malloc
    if (ptr == NULL) {
        return mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    }

    // Step 3: If total_size is 0, free the memory
    if (total_size == 0) {
        munmap(ptr, total_size); // Free the memory and return NULL
        return NULL;
    }

    // Step 4: Allocate new memory with mmap for the new size
    void *new_ptr = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (new_ptr == MAP_FAILED) {
        return NULL; // mmap failed
    }

    // Step 5: Copy old data to new allocation and free the old memory
    memcpy(new_ptr, ptr, total_size); // Copy old data (up to total_size)
    munmap(ptr, total_size); // Free the old memory

    return new_ptr;
}
