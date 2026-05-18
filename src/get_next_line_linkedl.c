#include "../include/get_next_line.h"

char	*ft_strchr(const char *str, int ch)
{
	while (*str)
	{
		if (*str == (char)ch)
			return ((char *)str);
		str++;
	}
	if (ch == '\0')
		return ((char *)str);
	return (NULL);
}

char	found_newline(t_list *list)
{
	while (list)
	{
		if (ft_strchr(list->content, '\n'))
			return (1);
		list = list->next;
	}
	return (0);
}

void	create_list(t_list **list, int fd)
{
	int		char_read;
	char	*buffer;

	while (!found_newline(*list))
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return ;
		char_read = read(fd, buffer, BUFFER_SIZE);
		if (char_read <= 0 || !char_read)
		{
			free(buffer);
			return ;
		}
		buffer[char_read] = '\0';
		ft_lstadd_back(list, ft_lstnew(buffer));
	}
}

int	ft_strlen(const char *str)
{
	int	length;

	length = 0;
	while (str[length])
		length++;
	return (length);
}

int	len_to_newline(t_list *list)
{
	int		length;
	char	*newline_pos;

	length = 0;
	while (list)
	{
		newline_pos = ft_strchr(list->content, '\n');
		if (newline_pos)
		{
			length += (newline_pos - (char *)list->content) + 1;
			break ;
		}
		length += ft_strlen(list->content);
		list = list->next;
	}
	return (length);
}

void	ft_strcat(char *dest, const char *src)
{
	char	*dest_end;

	dest_end = dest + ft_strlen(dest);
	while (*src)
	{
		*dest_end = *src;
		dest_end++;
		src++;
	}
	*dest_end = '\0';
}

void	ft_strncat(char *dest, const char *src, size_t n)
{
	char	*dest_end;
	size_t	i;

	dest_end = dest + ft_strlen(dest);
	i = 0;
	while (src[i] && i < n)
	{
		dest_end[i] = src[i];
		i++;
	}
	dest_end[i] = '\0';
}

char	*get_line(t_list *list, int fd)
{
	char	*next_str;
	int		str_length;
	char	*newline_pos;

	if (!list || !fd)
		return (NULL);
	str_length = len_to_newline(list);
	next_str = (char *)malloc(sizeof(char) * (str_length + 1));
	if (!next_str)
		return (NULL);
	next_str[0] = '\0';
	while (list)
	{
		newline_pos = ft_strchr(list->content, '\n');
		if (newline_pos)
		{
			ft_strncat(next_str, list->content,
				(size_t)(newline_pos - (char *)list->content + 1));
			break ;
		}
		ft_strcat(next_str, list->content);
		list = list->next;
	}
	return (next_str);
}

char	*ft_strdup(const char *src)
{
	int		length;
	int		i;
	char	*dup;

	length = ft_strlen(src);
	dup = (char *)malloc(sizeof(char) * (length + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < length)
	{
		dup[i] = src[i];
		i++;
	}
	dup[length] = '\0';
	return (dup);
}

void	polish_list(t_list **list)
{
	char	*newline_pos;
	char	*remaining_str;
	t_list	*temp;

	while (*list)
	{
		newline_pos = ft_strchr((*list)->content, '\n');
		if (newline_pos)
		{
			remaining_str = ft_strdup(newline_pos + 1);
			free((*list)->content);
			(*list)->content = remaining_str;
			break ;
		}
		temp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = temp;
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	create_list(&list, fd);
	next_line = get_line(list, fd);
	polish_list(&list);
	return (next_line);
}
