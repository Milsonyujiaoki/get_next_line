#include "libft.h"

/*
** =========================================================
**  linked list (s_list) — implementation
** =========================================================
*/

t_list  *ft_lstnew(void *content)
{
    t_list *node;

    node = (t_list *)ft_malloc(sizeof(t_list));
    if (!node)
        return (NULL);
    node->content = content;
    node->next = NULL;
    return (node);
}

void    ft_lstadd_front(t_list **lst, t_list *new_node)// Estou recebendo o ponteiro para a cabeça da lista (lst) e o nó a ser adicionado (new_node). O objetivo é inserir new_node no início da lista.
{
    if (!lst || !new_node)
        return ;
    new_node->next = *lst;
    *lst = new_node;
}
int     ft_lstsize(t_list *lst)
{
    int size;

    size = 0;
    while (lst)
    {
        size++;
        lst = lst->next;
    }
    return (size);
}
t_list  *ft_lstlast(t_list *lst)
{
   
    if (!lst)
    {
        return NULL;
    }
    
    while(lst->next != NULL)
    {
        lst = lst->next;
    }
    return lst;
}
void    ft_lstadd_back(t_list **lst, t_list *new_node)
{
    if(!lst || !new_node)
    {
        return ;
    }
    if (*lst == NULL)
    {
        *lst = new_node;
    }
    else
    {
        t_list *last = ft_lstlast(*lst);
        last->next = new_node;
    }
}
void    ft_lstdelone(t_list *lst, void (*del)(void *))
{
    if (!lst)
        return ;
    if (del)
        del(lst->content);
    ft_free(lst);
}
void    ft_lstclear(t_list **lst, void (*del)(void *))
{   
    t_list  *temp;

    if (!lst || !del)
        return ;

    while (*lst)
    {
        temp = (*lst)->next;
        ft_lstdelone(*lst, del);
        *lst = temp;
    }
    
}

void    ft_lstiter(t_list *lst, void (*f)(void *))
{
    // Complexidade de tempo: O() - depende da função f aplicada a cada nó. Se f for O(1), a complexidade geral será O(n), onde n é o número de nós na lista, pois precisamos iterar por cada nó da lista exatamente uma vez para aplicar a função f. Se a função f tiver uma complexidade maior, isso deve ser considerado na análise geral, mas a iteração em si é linear em relação ao número de nós. No pior dos casos (onde f é O(n) para cada nó), a complexidade total seria O(n²). No entanto, se f for O(1), a complexidade geral é O(n).

    // Complexidade de espaço: O(1) - a função utiliza uma quantidade constante de espaço adicional, independentemente do número de nós na lista. Ela apenas mantém um ponteiro para o nó atual durante a iteração, e não aloca espaço adicional proporcional ao tamanho da lista. Portanto, a complexidade de espaço é constante.

    if (!lst || !f)
        return ;

    while(lst != NULL)
    {
        f(lst->content);
        lst = lst->next;
    }
}
t_list  *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
    // Todo: Implementar a função ft_lstmap que cria uma nova lista aplicando a função f ao conteúdo de cada nó da lista original (lst). Se ocorrer um erro durante a criação de um novo nó, a função deve aplicar a função del ao conteúdo dos nós já criados e liberar a memória alocada para a nova lista antes de retornar NULL.

    //Complexidade de tempo: O(n²) - onde n é o número de nós na lista original (lst), pois precisamos percorrer cada nó da lista para aplicar a função f e criar os novos nós. usamos ft_lstadd_back para adicionar cada novo nó ao final da nova lista, o que tem complexidade O(n) para cada adição, resultando em O(n²) no total. Se a função f for O(1), a complexidade geral ainda será O(n²) devido à adição de nós. Se a função f tiver uma complexidade maior, isso deve ser considerado na análise geral.
    //Complexidade de espaço: O(n) - onde n é o número de nós na lista original (lst), pois no pior caso, a nova lista criada pode ter o mesmo número de nós que a lista original. Cada nó da nova lista armazena um ponteiro para o conteúdo transformado, e a função f pode criar novos objetos que também ocupam espaço. Se ocorrer um erro durante a criação de um novo nó, a função del será chamada para liberar o conteúdo dos nós já criados, mas isso não afeta a complexidade de espaço geral, que permanece O(n) devido à necessidade de armazenar os nós da nova lista.

    t_list	*new_list;
	t_list	*new_node;
	void	*new_content;

    if (!lst || !f)
        return (NULL);
    new_list = NULL;
    while (lst)    {
        new_content = f(lst->content);
        if (!new_content)        {
            ft_lstclear(&new_list, del);
            return (NULL);
        }
        new_node = ft_lstnew(new_content);
        if (!new_node)        {
            ft_lstclear(&new_list, del);
            return (NULL);
        }
        ft_lstadd_back(&new_list, new_node);
        lst = lst->next;
    }
    return (new_list);
}
void   ft_print_list(t_list *lst)
{
    // Se a lista estiver vazia, imprime uma representação clara e sai
    if (!lst)
    {
        ft_putstr_fd("NULL\n", 1);
        return ;
    }
    
    while (lst)
    {
        // Realiza o cast explícito de void* para char* para evitar warnings
        ft_putstr_fd((char *)lst->content, 1);
        
        if (lst->next)
        {
            ft_putstr_fd(" -> ", 1);
        }
        lst = lst->next; // Avança para o próximo nó
    }
    ft_putstr_fd(" -> NULL\n", 1);
}

void    ft_printf_lst(t_list *lst, void (*print_data)(void *))
{
    if (!lst || !print_data)
    {
        ft_printf("╔═════════════════════════════════════════╗\n");
        ft_printf("║   List Status: \033[1;31m[ VAZIA OU SEM PRINT ]\033[0m   ║\n");
        ft_printf("╚═════════════════════════════════════════╗\n");
        return ;
    }

    ft_printf("\n\033[1;34m╔═══ Visualização de Lista Encadeada ════════════════\033[0m\n");
    
    while (lst)
    {
        ft_printf(" ┌──────────────────────────┐\n");
        ft_printf(" │ Node: \033[1;33m%p\033[0m       │\n", lst);
        
        // --- O SEGREDO ESTÁ AQUI ---
        // Imprime o início da linha e chama a função acessória para o conteúdo
        ft_printf(" │ Data: \033[1;32m");
        print_data(lst->content); 
        ft_printf("\033[0m\t    │\n");
        // ---------------------------

        ft_printf(" │ Next: %p │\n", lst->next);
        ft_printf(" └──────────────────────────┘\n");

        if (lst->next)
        {
            ft_printf("              \033[1;36m│\033[0m\n");
            ft_printf("              \033[1;36m▼\033[0m\n");
        }
        lst = lst->next;
    }
    ft_printf("              \033[1;31m╳ [ NULL ]\033[0m\n");
    ft_printf("\033[1;34m╚════════════════════════════════════════════════════╝\033[0m\n\n");
}

