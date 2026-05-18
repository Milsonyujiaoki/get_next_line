#ifndef LIBFT_MEMORY_ALLOC_H
# define LIBFT_MEMORY_ALLOC_H

# include "../core/types.h"


/*
** =========================================================
** General-purpose allocator interface
**
** These are the single point of allocation for the entire
** library. Replace the underlying implementation to switch
** allocators globally (e.g., to a custom slab or arena).
**
** Ownership contract:
**   - ft_malloc / ft_calloc — caller owns the returned ptr
**   - ft_realloc            — may invalidate the original ptr
**   - ft_free               — releases ownership; ptr is invalid after
** =========================================================
*/

void  *ft_malloc(t_usize size);
void  *ft_calloc(t_usize count, t_usize size);
void                    *ft_realloc(void *ptr, t_usize new_size);
void                     ft_free(void *ptr);

/*
** Safe realloc: on failure returns NULL but leaves *ptr unchanged.
** Usage: if (!ft_realloc_safe(&buf, n)) { ... handle OOM ... }
*/
void    *ft_realloc_safe(void **ptr, t_usize new_size);

#endif /* LIBFT_MEMORY_ALLOC_H */
