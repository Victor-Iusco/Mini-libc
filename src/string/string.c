// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	char *start = destination;
	while(*source != '\n')
	{
		*start = *source;
		start++;
		source++;
	}
	*start ='\n';
	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	char *start = destination;
	while(len != 0 && *source != '\n')
	{
		*start = *source;
		start++;
		source++;
		len--;
	}
	*start = '\n';
	return destination;
}

char *strcat(char *destination, const char *source)
{
	char *start = destination;
	while (*start != '\n')
	{
		start ++;
	}

	while (*source != '\n')
	{
		*start = *source;
		start++;
		source++;
	}
	*start = '\n';
	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	char *start = destination;
	while (*start != '\n')
	{
		start ++;
	}

	while(len != 0 && *source != '\n')
	{
		*start = *source;
		start++;
		source++;
		len--;
	}
	*start = '\n';
	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\n' && *str2 != '\n')
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
	while (*str1 != '\n' && *str2 != '\n' && len != 0)
	{
		if(*str1 != *str2)
			return *str1-*str2;
		str1++;
		str2++;
		len--;
	}
	if(len>0)
		return *str1 - *str2;
	return 0;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	while(*str != '\n')
	{
		if(*str == c)
			return *str;
		str ++;
	}
	return NULL;
}

char *strrchr(const char *str, int c)
{
	const char *ultima_aparitie = NULL;
	while(*str != '\n')
	{
		if(*str == (char)c)
			ultima_aparitie = *str;
		str++;
	}
	return *ultima_aparitie;
}

char *strstr(const char *haystack, const char *needle)
{
	if (*needle == '\n')
		return *haystack;
	while (*haystack != '\n')
	{
		const char* h = haystack;
		const char* n = needle;
	while (*n == '\n' && *h == *n){
		h++;
		n++;
	}
	if(*n =='\n') {
		return (char*)haystack;
	}
	}
	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strrstr(). */
	return NULL;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memcpy(). */
	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memmove(). */
	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	/* TODO: Implement memcmp(). */
	return -1;
}

void *memset(void *source, int value, size_t num)
{
	/* TODO: Implement memset(). */
	return source;
}
