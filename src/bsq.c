/*
** EPITECH PROJECT, 2018
** fs_understand_return_of_read
** File description:
** read
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int **create_my_array(char *buffer)
{
    int line = 0;
    int collumn;
    int i = 0;
    int **str = NULL;

    for (collumn = 0; buffer[collumn] != '\0'; collumn += 1) {
        if (buffer[collumn] == '\n')
            line = line + 1;
    }
    line = line - 1;
    collumn = collumn / line - 1;
    str = malloc(sizeof(int *) * (line + 1));
    if (str == NULL)
        return (NULL);
    str[line] = NULL;
    for (i = 0; i < line; i += 1) {
        str[i] = malloc(sizeof(int) * (collumn + 1));
        if (str[i] == NULL)
            return (NULL);
    }
    return (str);
}

int fs_open_file(char const *filepath)
{
    int fd;

    fd = open(filepath, O_RDONLY);
    if (fd == -1)
        return (84);
    return (fd);
}
void calculate_array(int **new_array, int line, int backup_column)
{
    int x = 0;
    int y = 0;
    int *a;
    int *b;
    int *c;
    int *d;
    int min = 0;

    while (x < line) {
        if (x != 0) {
            while (y < backup_column) {
                if (y != 0) {
                    if (new_array[x][y] != 0) {
                        a = &new_array[x - 1][y - 1];
                        b = &new_array[x - 1][y];
                        c = &new_array[x][y - 1];
                        d = &new_array[x][y];
                        if (*a != 0 || *b != 0 || *c != 0) {
                            if (*b >= *a && *c >= *a)
                                min = *a;
                            else if (*a >= *b && *c >= *b)
                                min = *b;
                            else
                                min = *c;
                        } else if (*a == 0 || *b == 0 || *c == 0)
                            new_array[x][y] = 1;
                        new_array[x][y] = min + 1;
                    }
                }
                y = y + 1;
            }
        }
        y = 0;
        x = x + 1;
    }
}
void remplace_x_array(int **new_array,char *buffer, int line,
                      int backup_collumn)
{
    int x = 0;
    int y = 0;
    int max_x = 0;
    int max_y = 0;
    int max = 0;
    int min_x = 0;
    int min_y = 0;

    while (x < line) {
        y = 0;
        while (y < backup_collumn) {
            if (new_array[x][y] > new_array[max_x][max_y]) {
                max_x = x;
                max_y = y;
            }
            y = y + 1;
        }
        x = x + 1;
    }
    max = new_array[max_x][max_y];
    for (x = max_x; x > max_x - max; x -= 1) {
        for (y = max_y; y > max_y - max; y -= 1) {
            buffer[y + (x * (backup_collumn + 1))] = 'x';
        }
    }
}

void replace_my_array(int fd, char *buffer, int size)
{
    int ret = read(fd, buffer, size);
    int i = 0;
    int **new_array;
    int line = 0;
    int backup_column = 0;
    int collumn = 0;
    int k = 0;

    buffer[ret] = '\0';
    while (buffer[i] != '\n')
    	i = i + 1;
    i = i + 1;
    k = i;
    new_array = create_my_array(buffer);
    while (buffer[i] != '\0') {
        if (buffer[i] == '.') {
            new_array[line][collumn] = 1;
            collumn = collumn + 1;
        } else if (buffer[i] == 'o') {
            new_array[line][collumn] = 0;
            collumn = collumn + 1;
        } else if (buffer[i] == '\n') {
            backup_column = collumn;
            collumn = 0;
            line = line + 1;
        }
        i = i + 1;
    }
    calculate_array(new_array, line, backup_column);
    remplace_x_array(new_array,buffer + k, line, backup_column);
    i = 0;
    write(1, buffer+k, size - k );
}
