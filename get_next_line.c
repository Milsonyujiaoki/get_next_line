/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <student.42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-21 11:48:51 by marvin            #+#    #+#             */
/*   Updated: 2026-05-21 11:48:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** gnl_strlen — comprimento de s (NULL-safe)
*/
static size_t	gnl_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

/*
** gnl_strjoin — anexa n bytes de buf ao final de s1 (libera s1).
** Retorna nova string ou NULL em caso de falha.
*/
static char	*gnl_strjoin(char *s1, char *buf, int n)
{
	size_t	len1;
	size_t	j;
	char	*result;

	len1 = gnl_strlen(s1);
	result = malloc(len1 + (size_t)n + 1);
	if (!result)
		return (free(s1), NULL);
	j = 0;
	while (j < len1)
	{
		result[j] = s1[j];
		j++;
	}
	j = 0;
	while (j < (size_t)n)
	{
		result[len1 + j] = buf[j];
		j++;
	}
	result[len1 + j] = '\0';
	free(s1);
	return (result);
}

/*
** gnl_extract — extrai do remainder a linha até (e incluindo) '\n'.
** Se não há '\n', extrai tudo (último bloco sem newline no EOF).
*/
static char	*gnl_extract(const char *s)
{
	size_t	i;
	size_t	j;
	char	*line;

	if (!s || !*s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = s[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}


/*
** gnl_trim — remove do remainder tudo até (e incluindo) '\n' (libera o antigo).
** Se não há '\n' restante, libera e retorna NULL.
*/
static char	*gnl_trim(char *s)
{
	size_t	i;
	size_t	j;
	char	*new_s;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
		return (free(s), NULL);
	i++;
	new_s = malloc(gnl_strlen(s + i) + 1);
	if (!new_s)
		return (free(s), NULL);
	j = 0;
	while (s[i + j])
	{
		new_s[j] = s[i + j];
		j++;
	}
	new_s[j] = '\0';
	free(s);
	return (new_s);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*buf;
	char		*line;
	int			n;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	n = 1;
	while (n > 0)
	{
		const char	*p;

		p = remainder;
		while (p && *p && *p != '\n')
			p++;
		if (p && *p == '\n')
			break ;
		n = read(fd, buf, BUFFER_SIZE);
		if (n < 0)
			return (free(buf), free(remainder), remainder = NULL, NULL);
		if (n == 0)
			break ;
		buf[n] = '\0';
		remainder = gnl_strjoin(remainder, buf, n);
		if (!remainder)
			return (free(buf), NULL);
	}
	free(buf);
	if (!remainder || !*remainder)
		return (free(remainder), remainder = NULL, NULL);
	line = gnl_extract(remainder);
	if (!line)
		return (free(remainder), remainder = NULL, NULL);
	char *tmp = gnl_trim(remainder);
	remainder = tmp;
	return (line);
}
