/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dev-yuji <dev-yuji@student.42.sp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 21:08:08 by dev-yuji          #+#    #+#             */
/*   Updated: 2026/05/21 21:19:55 by dev-yuji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# define BUFFER_SIZE 42
# define OPEN_MAX 1024

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

char	*get_next_line_bonus(int fd);

char	*read_and_join(int fd, char *stash);
char	*extract_line(char *stash);
char	*clean_stash(char *stash);

#endif
