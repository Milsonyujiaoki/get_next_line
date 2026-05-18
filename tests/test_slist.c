# include <get_next_line.h>



int main(int ac, char **av)
{
    t_list *root;
    t_list *node1;
    t_list *node2;

    root = malloc(sizeof(t_list));
    node1 = malloc(sizeof(t_list));
    node2 = malloc(sizeof(t_list));

    root->str_buf = 42;
    node1->str_buf = 420;
    node2->str_buf = 4200;

    root->next = node1;
    root->next->next = node2;
    root->next->next->next = NULL;

    free(root);
    free(node1);
    free(node2);
}