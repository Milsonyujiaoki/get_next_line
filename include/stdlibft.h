#ifndef LIBFT_STDLIB_FT_H
# define LIBFT_STDLIB_FT_H

# include "types.h"

/*
** =========================================================
** stdlib — string conversion utilities
**
** Memory allocation (ft_malloc / ft_calloc / ft_free /
** ft_realloc) lives in memory/alloc.h.
** =========================================================
*/

/* String → numeric conversions */
int        ft_atoi(const char *str);
long       ft_atol(const char *str);
long long  ft_atoll(const char *str);
double     ft_atof(const char *str);

/* Numeric → string conversions */
/* Returns a heap-allocated NUL-terminated string.
** Caller must ft_free() the result. */
char      *ft_itoa(int n);

#endif /* LIBFT_STDLIB_FT_H */