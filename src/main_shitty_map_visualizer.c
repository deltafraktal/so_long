/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shitty_map_visualizer.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 04:21:29 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/04 17:47:05 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"
// debug.c
// src/parsing/parse_map.c
static int  count_lines(char *path)
{
int     fd;
int     count;
char    *line;
fd = open(path, O_RDONLY);
if (fd < 0)
return (0);
count = 0;
line = get_next_line(fd);
while (line)
    {
count++;
free(line);
line = get_next_line(fd);
    }
close(fd);
return (count);
}
static void parse_line(t_game *game, char *line, int y)
{
int x;
x = 0;
while (line[x] && line[x] != '\n')
    {
if (line[x] == 'C')
game->collectibles++;
else if (line[x] == 'P')
        {
game->player_x = x;
game->player_y = y;
        }
game->map[y][x] = line[x];
x++;
    }
game->map[y][x] = '\0';
}
void    parse_map(char *path, t_game *game)
{
int     fd;
int     y;
char    *line;
game->rows = count_lines(path);
game->map = malloc(sizeof(char *) * (game->rows + 1));
if (!game->map)
return ;
fd = open(path, O_RDONLY);
if (fd < 0)
return ;
y = 0;
line = get_next_line(fd);
while (line)
    {
game->cols = ft_strlen(line);
game->map[y] = malloc(sizeof(char) * (game->cols + 1));
if (!game->map[y])
return ;
parse_line(game, line, y);
free(line);
y++;
line = get_next_line(fd);
    }
game->map[y] = NULL;
close(fd);
}
void    debug_map(t_game *game)
{
int y;
int x;
y = 0;
while (y < game->rows)
    {
x = 0;
while (x < game->cols)
        {
if (game->map[y][x] == '1')
ft_printf("\033[40m  \033[0m");
else if (game->map[y][x] == '0')
ft_printf("\033[47m  \033[0m");
else if (game->map[y][x] == 'P')
ft_printf("\033[44m P\033[0m");
else if (game->map[y][x] == 'C')
ft_printf("\033[43m C\033[0m");
else if (game->map[y][x] == 'E')
ft_printf("\033[42m E\033[0m");
else
ft_printf("\033[41m ?\033[0m");
x++;
        }
ft_printf("\n");
y++;
    }
ft_printf("collectibles: %d | moves: %d\n",
game->collectibles, game->moves);
}
int main(int ac, char **av)
{
t_game  game;
if (ac != 2)
return (ft_printf("Usage: ./so_long map.ber\n"), 1);
parse_map(av[1], &game);
return (0);
}