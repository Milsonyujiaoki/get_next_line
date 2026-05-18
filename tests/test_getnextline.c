# include "../include/get_next_line.h"

int main(void)
{
    int fd;
    char *next_line;
    int  lines = 1;


    fd = open("tests/txt1.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return 1;
    }

    while ((next_line = get_next_line(fd)) != NULL)
    {
        printf("%d->%s", lines++, next_line);
        free(next_line);
    }
    close(fd);
    return 0;
}