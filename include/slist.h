#ifndef LIBFT_DS_SLIST_H
# define LIBFT_DS_SLIST_H

/*
** =========================================================
** linked list (t_list) — public header
** =========================================================
*/
typedef struct s_list
{
	void            *content; //transforma em tipo generico que aceita *int, *char, struct s_user *, etc
	struct s_list   *next; //aponta para o proximo nó da lista, ou NULL se for o ultimo nó
}   t_list;

t_list  *ft_lstnew(void *content); //cria um novo nó com o conteúdo fornecido e retorna um ponteiro para ele. O campo next é inicializado como NULL.
void    ft_lstadd_front(t_list **lst, t_list *new_node); //adiciona o nó new_node no início da lista apontada por lst. O campo next de new_node é atualizado para apontar para o nó que era anteriormente o primeiro nó da lista.
int     ft_lstsize(t_list *lst); //retorna o número de nós na lista apontada por lst. Percorre a lista contando os nós até chegar ao final (quando next é NULL).
t_list  *ft_lstlast(t_list *lst); //retorna um ponteiro para o último nó da lista apontada por lst. Percorre a lista até encontrar o nó cujo campo next é NULL, indicando que é o último nó.
void    ft_lstadd_back(t_list **lst, t_list *new_node); //adiciona o nó new_node no final da lista apontada por lst. O campo next do último nó é atualizado para apontar para new_node.
void    ft_lstdelone(t_list *lst, void (*del)(void *)); //remove o nó lst da lista, aplicando a função del ao conteúdo do nó antes de liberar a memória do nó.
void    ft_lstclear(t_list **lst, void (*del)(void *)); //remove todos os nós da lista apontada por lst, aplicando a função del ao conteúdo de cada nó antes de liberar a memória dos nós.
void    ft_lstiter(t_list *lst, void (*f)(void *)); //aplica a função f ao conteúdo de cada nó da lista apontada por lst.
t_list  *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *)); //cria uma nova lista aplicando a função f ao conteúdo de cada nó da lista apontada por lst. Se ocorrer um erro, aplica a função del ao conteúdo dos nós já criados e libera a memória.

void   ft_print_list(t_list *lst); //função auxiliar para imprimir o proximo no e o conteudo do nó, usando ft_putstr_fd para imprimir o conteúdo, e ft_putstr para imprimir a seta "->" entre os nós. 

void    ft_printf_lst(t_list *lst, void (*print_data)(void *)); //função auxiliar para imprimir o status da lista usando ft_printf, indicando se a lista está vazia ou não, e mostrando o conteúdo de cada nó de forma formatada.
#endif /* LIBFT_DS_SLIST_H */
