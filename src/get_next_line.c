#include "../include/get_next_line.h"

static char *ft_strchr_gnl(const char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    if (c == '\0')
        return ((char *)s);
    return (NULL);
}

static int found_newline(t_list *list)
{
    while (list)
    {
        if (ft_strchr_gnl(list->content, '\n'))
            return (1);
        list = list->next;
    }
    return (0);
}

static void create_list(t_list **list, int fd)
{
    char    *buffer;
    int     chars_read;

    while (!found_newline(*list))
    {
        buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
        if (!buffer)
            return;

        chars_read = read(fd, buffer, BUFFER_SIZE);
        if (chars_read <= 0)
        {
            free(buffer);
            return;
        }

        buffer[chars_read] = '\0';
        ft_lstadd_back(list, ft_lstnew(buffer));
    }
}


static size_t ft_strlen_gnl(const char *str)
{
    size_t len = 0;
    while (str[len]){
        len++;
    }
    return (len);
}


static int len_to_newline(t_list *list)
{
    int     len = 0;
    char    *nl_pos;

    while (list)
    {
        nl_pos = ft_strchr_gnl(list->content, '\n');
        if (nl_pos)
        {
            len += (nl_pos - (char *)list->content) + 1;
            return (len);
        }
        len += ft_strlen_gnl(list->content);
        list = list->next;
    }
    return (len);
}

void *ft_strcat(char *dest, const char *src)
{
    char *dest_start = dest;

    while (*dest)
        dest++;
    while (*src)
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return (dest_start);
}

static char *get_line(t_list *list)
{
    char    *line;
    int     len;
    t_list  *tmp = list;

    if (!list)
        return (NULL);

    len = len_to_newline(list);
    line = malloc(sizeof(char) * (len + 1));
    if (!line)
        return (NULL);

    line[0] = '\0';

    while (tmp)
    {
        char *nl_pos = ft_strchr_gnl(tmp->content, '\n');
        if (nl_pos)
        {
            ft_strcat(line, tmp->content);   
            break;
        }
        ft_strcat(line, tmp->content);
        tmp = tmp->next;
    }
    return (line);
}




static char *ft_strdup(const char *s)
{
    char *dup = malloc(ft_strlen_gnl(s) + 1);
    if (dup)
        ft_strcat(dup, s);
    return (dup);
}

void polish_list(t_list **list)
{
    char    *nl_pos;
    t_list  *tmp;

    while (*list)
    {
        nl_pos = ft_strchr_gnl((*list)->content, '\n');
        if (nl_pos)
        {
            char *remaining = ft_strdup(nl_pos + 1);
            free((*list)->content);
            (*list)->content = remaining;
            return;
        }
        // Sem newline → remover nó
        tmp = (*list)->next;
        free((*list)->content);
        free(*list);
        *list = tmp;
    }
}

char *get_next_line(int fd)
{
    static t_list   *list = NULL;
    char            *line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
        return (NULL);

    create_list(&list, fd);
    line = get_line(list);
    polish_list(&list);

    return (line);
}