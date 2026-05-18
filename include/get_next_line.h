#ifndef GET_NXT_LN_H
# define GET_NXT_LN_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>

/* ── §1  t_list  ─────────────────────────────────────────────────────────
** Singly-linked list — required by the 42 norm.
** ft_lst* functions operate on this type.
** ─────────────────────────────────────────────────────────────────────────*/

typedef struct s_list
{
	void            *content;
	struct s_list   *next;
}   t_list;

t_list  *ft_lstnew(void *content);
void     ft_lstadd_front(t_list **lst, t_list *new_node);
int      ft_lstsize(t_list *lst);
t_list  *ft_lstlast(t_list *lst);
void     ft_lstadd_back(t_list **lst, t_list *new_node);
void     ft_lstdelone(t_list *lst, void (*del)(void *));
void     ft_lstclear(t_list **lst, void (*del)(void *));
void     ft_lstiter(t_list *lst, void (*f)(void *));
t_list  *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

void     ft_print_list(t_list *lst);
void     ft_printf_lst(t_list *lst, void (*print_data)(void *));


/* ── §1  get_next_line  ─────────────────────────────────────────────────────────

** 
** ─────────────────────────────────────────────────────────────────────────*/

char  *get_next_line(int fd);






#endif
