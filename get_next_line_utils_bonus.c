/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev-yuji <dev-yuji@student.42.sp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 21:07:26 by dev-yuji          #+#    #+#             */
/*   Updated: 2026/05/21 21:37:26 by dev-yuji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_and_join(int fd, char *stash)
{
	char	*buffer;
	size_t	i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE +1);
	if (!buffer)
		return (NULL);
	
}

char	*extract_line(char *stash)
{

}

char	*clean_stash(char *stash)
{

}
