#include <stdlib.h>
#include "memory/alloc.h"

/*
** ft_malloc — wraps the system allocator.
** Future: replace body with a custom slab / arena allocator.
*/
void    *ft_malloc(t_usize size)
{
    if (size == 0)
        return (NULL);
    return (malloc(size));
}
