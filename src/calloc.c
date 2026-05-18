#include "libft.h"
#include "memory/alloc.h"


void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total_size;

	total_size = count * size;
	if (size != 0 && (total_size / size) != count)
		return (NULL);
	ptr = ft_malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}
