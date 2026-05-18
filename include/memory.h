#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

// Memory functions

void *ft_memset( void *dest, int ch, size_t count );

void *ft_memcpy(void *dest, const void *src, size_t count);

void *ft_memccpy(void *restrict dest, const void *restrict src,int c, size_t count);

void *ft_memmove(void *dest, const void *src, size_t count);

int ft_memcmp(const void *lhs, const void *rhs, size_t count);

void *ft_memchr(const void *ptr, int value, size_t count);

void *ft_bzero(void *ptr, size_t count);

#endif /* MEMORY_H */