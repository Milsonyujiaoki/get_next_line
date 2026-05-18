#include "../include/get_next_line.h"

/* =========================================================
**  Linked List Functions
** ========================================================= */

t_list *ft_lstnew(void *content)
{
    t_list *node;

    node = (t_list *)malloc(sizeof(t_list));
    if (!node)
        return (NULL);
    node->content = content;
    node->next = NULL;
    return (node);
}

void ft_lstadd_front(t_list **lst, t_list *new_node)
{
    if (!lst || !new_node)
        return ;
    new_node->next = *lst;
    *lst = new_node;
}

int ft_lstsize(t_list *lst)
{
    int size = 0;

    while (lst)
    {
        size++;
        lst = lst->next;
    }
    return (size);
}

t_list *ft_lstlast(t_list *lst)
{
    if (!lst)
        return (NULL);
    while (lst->next)
        lst = lst->next;
    return (lst);
}

void ft_lstadd_back(t_list **lst, t_list *new_node)
{
    t_list *last;

    if (!lst || !new_node)
        return ;
    if (*lst == NULL)
    {
        *lst = new_node;
        return ;
    }
    last = ft_lstlast(*lst);
    if (last == NULL)
    {
        *lst = new_node;
        return ;
    } else {
        last->next = new_node;
        new_node->next = NULL;
        return ;
    }

    
}

void ft_lstdelone(t_list *lst, void (*del)(void *))
{
    if (!lst)
        return ;
    if (del)
        del(lst->content);
    free(lst);
}

void ft_lstclear(t_list **lst, void (*del)(void *))
{
    t_list *current;
    t_list *temp;

    

    if (!lst || !del)
        return ;
    current = *lst;
    while (current != NULL)
    {
        temp = current;
        current = current->next;
        ft_lstdelone(temp, del);
    }
    *lst = NULL;
}

void ft_lstiter(t_list *lst, void (*f)(void *))
{
    if (!lst || !f)
        return ;
    while (lst)
    {
        f(lst->content);
        lst = lst->next;
    }
}

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
    t_list *new_list = NULL;
    t_list *new_node;
    void   *new_content;

    if (!lst || !f)
        return (NULL);

    while (lst)
    {
        new_content = f(lst->content);
        if (!new_content)
        {
            ft_lstclear(&new_list, del);
            return (NULL);
        }

        new_node = ft_lstnew(new_content);
        if (!new_node)
        {
            free(new_content);           // importante!
            ft_lstclear(&new_list, del);
            return (NULL);
        }

        ft_lstadd_back(&new_list, new_node);
        lst = lst->next;
    }
    return (new_list);
}

/* Funções de debug (opcionais) */
void ft_print_list(t_list *lst)
{
    if (!lst)
    {
        printf("NULL\n");
        return ;
    }
    while (lst)
    {
        printf("%s", (char *)lst->content);
        if (lst->next)
            printf(" -> ");
        lst = lst->next;
    }
    printf(" -> NULL\n");
}

void printf_lst(t_list *lst, void (*print_data)(void *))
{
    if (!lst || !print_data)
    {
        printf("List is empty or no print function\n");
        return ;
    }

    printf("\n╔═══ Linked List ═══════════════════════╗\n");
    while (lst)
    {
        printf("├─ Node: %p\n", lst);
        printf("│  Data: ");
        print_data(lst->content);
        printf("\n│  Next: %p\n", lst->next);
        lst = lst->next;
    }
    printf("╚══════════════════════════════════════╝\n");
}