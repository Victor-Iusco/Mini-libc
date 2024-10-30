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

	mem_list_add(ptr, size);

    return ptr;
}

void *calloc(size_t nmemb, size_t size)
{
	size_t total_size = nmemb * size;
    if (nmemb != 0 && total_size / nmemb != size) {
        return NULL;
    }
    void *ptr = malloc(total_size);
    if (!ptr) {
        return NULL;
    }
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
    if (size == 0) {
        free(ptr);
        return NULL;
    }
    void *new_ptr = mremap(ptr, 0, size, MREMAP_MAYMOVE);
    if (new_ptr == MAP_FAILED) {
        new_ptr = malloc(size);
        if (new_ptr) {
            memcpy(new_ptr, ptr, size);
            free(ptr);
        }
    }

    return new_ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    if (nmemb && size > (size_t)-1 / nmemb) {
        errno = ENOMEM;
        return NULL;
    }

    size_t total_size = nmemb * size;
    if (ptr == NULL) {
        return mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    }

    if (total_size == 0) {
        munmap(ptr, total_size);
        return NULL;
    }
    void *new_ptr = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (new_ptr == MAP_FAILED) {
        return NULL;
    }
    memcpy(new_ptr, ptr, total_size);
    munmap(ptr, total_size);
    return new_ptr;
}
