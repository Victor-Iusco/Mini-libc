// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	char *start = destination;
	while(*source != '\0')
	{
		*start = *source;
		start++;
		source++;
	}
	*start ='\0';
	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	char *start = destination;
	while(len > 0 && *source != '\0')
	{
		*start = *source;
		start++;
		source++;
		len--;
	}

	while(len > 0)
	{
		*start = '\0';
		start++;
		len--;
	}
	return destination;
}

char *strcat(char *destination, const char *source)
{
	char *start = destination;
	while (*start != '\0')
	{
		start++;
	}

	while (*source != '\0')
	{
		*start = *source;
		start++;
		source++;
	}
	*start = '\0';
	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	char *start = destination;
	while (*start != '\0')
	{
		start++;
	}

	while(len != 0 && *source != '\0')
	{
		*start = *source;
		start++;
		source++;
		len--;
	}
	*start = '\0';
	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if(*str1 != *str2)
			return *str1-*str2;
		str1++;
		str2++;
	}
	return *str1 - *str2;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	while (*str1 != '\0' && *str2 != '\0' && len != 0)
	{
		if(*str1 != *str2)
			return *str1-*str2;
		str1++;
		str2++;
		len--;
	}
	if(len > 0)
		return *str1 - *str2;
	return 0;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	while (*str != '\0')
	{
    	str++;
    	i++;
	}

	return i;
}

char *strchr(const char *str, int c)
{
	while(*str != '\0')
	{
		if(*str == c)
			return (char *)str;
		str++;
	}
	return NULL;
}

char *strrchr(const char *str, int c)
{
	const char *ultima_aparitie = NULL;
	while(*str != '\0')
	{
		if(*str == (char)c)
			ultima_aparitie = str;
		str++;
	}
	return (char *)ultima_aparitie;
}

char *strstr(const char *haystack, const char *needle) {
    if (*needle == '\0') {
        return (char *)haystack;
    }
    while (*haystack != '\0') {
        const char *h = haystack;
        const char *n = needle;

        while (*n != '\0' && *h == *n) {
            h++;
            n++;
        }
        if (*n == '\0') {
            return (char *)haystack;
        }
        haystack++;
    }
    return NULL;
}

char *strrstr(const char *haystack, const char *needle) {
    if (*needle == '\0') {
        return (char *)haystack;
    }
    char *last_occurrence = NULL;
    while (*haystack != '\0') {
        const char *h = haystack;
        const char *n = needle;

        while (*n != '\0' && *h == *n) {
            h++;
            n++;
        }
        if (*n == '\0') {
            last_occurrence = (char *)haystack;
        }
        haystack++;
    }
    return last_occurrence;
}


void *memcpy(void *destination, const void *source, size_t num) {
    char *dest = (char *)destination;
    const char *src = (const char *)source;
    for (size_t i = 0; i < num; i++) {
        dest[i] = src[i];
    }
    return destination;
}

void *memmove(void *destination, const void *source, size_t num) {
    char *dest = (char *)destination;
    const char *src = (const char *)source;
    if (dest < src) {
        for (size_t i = 0; i < num; i++) {
            dest[i] = src[i];
        }
    } else {
        for (size_t i = num; i > 0; i--) {
            dest[i - 1] = src[i - 1];
        }
    }
    return destination;
}


int memcmp(const void *ptr1, const void *ptr2, size_t num) {
    const unsigned char *p1 = (const unsigned char *)ptr1;
    const unsigned char *p2 = (const unsigned char *)ptr2;
    for (size_t i = 0; i < num; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] - p2[i];
        }
    }
    return 0;
}

void *memset(void *source, int value, size_t num) {
    unsigned char *ptr = (unsigned char *)source;
    for (size_t i = 0; i < num; i++) {
        ptr[i] = (unsigned char)value;
    }
    return source;
}
