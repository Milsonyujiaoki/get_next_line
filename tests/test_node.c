#include "../include/get_next_line.h"
#include <stdio.h>

void multiply(void *content)
{
    *(int *)content *= 2;
}

void print_int(void *content)
{
    printf("%d\n", *(int *)content);
}

int main(void)
{
    t_list *root = NULL;

    ft_lstadd_back(&root, ft_lstnew(malloc(sizeof(int))));
    ft_lstadd_back(&root, ft_lstnew(malloc(sizeof(int))));
    ft_lstadd_back(&root, ft_lstnew(malloc(sizeof(int))));

    *(int *)root->content = 42;
    *(int *)root->next->content = 420;
    *(int *)root->next->next->content = 4200;

    printf("Original:\n");
    ft_lstiter(root, print_int);

    ft_lstiter(root, multiply);

    printf("\nAfter x2:\n");
    ft_lstiter(root, print_int);

    ft_lstclear(&root, free);
    return 0;
}