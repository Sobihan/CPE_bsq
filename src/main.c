/*
** EPITECH PROJECT, 2018
** main
** File description:
** main
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

int fs_open_file(char const *filepath);
void replace_my_array(int fd, char *buffer, int size);

int main(int ac, char **av)
{
    int fd;
    int size;
    char *buffer;

    struct stat file_stat;
    if (stat(av[1], &file_stat) < 0)
        return (1);
    fd = fs_open_file(av[1]);
    size = file_stat.st_size;
    buffer = malloc(sizeof(char) * (size + 1));
    replace_my_array(fd, buffer, size);
    close(fd);
    return (0);
}
