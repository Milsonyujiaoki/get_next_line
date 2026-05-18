# include "get_next_line.h"


char  *get_next_line(int fd)
{
    static t_list  *list = NULL;
    char           *next_line;

    if( fd < 0 || BUFFER_SIZE <=0 || read(fd, &next_line, 0) < 0)
    {
        return NULL;
    }

    ft_lstnew(&list, fd);

}   
