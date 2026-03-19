/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 22:42:38 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/19 22:59:28 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

void set_x(t_game *game)
{
	int	y;
	int	x;
	int	i;
	
	game->x = malloc(sizeof(t_enemy) * game->x_count);
	if (!game->x)
		return;
	y = 0;
	i = 0;
	while (y < game->map_rows - 1)
	{
		x = 0;
		while (x < game->map_cols - 1)
		{
			if (game->map[y][x] == 'X')
			{
				game->x[i].y = y;
				game->x[i].x = x;
				game->x[i].dir = 1;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	move_x(t_game *game)
{
	int     i;
    int     new_x;

	if (game->won == 2)
        return ;
    i = 0;
    while (i < game->x_count)
    {
        new_x = game->x[i].x + game->x[i].dir;
        if (game->map[game->x[i].y][new_x] == '1'
			|| game->map[game->x[i].y][new_x] == 'E')
            game->x[i].dir *= -1;
        else
        {
            game->map[game->x[i].y][game->x[i].x] = '0';
            game->x[i].x = new_x;
            if (new_x == game->p_x && game->x[i].y == game->p_y)
                pop_up(game, 1);
            game->map[game->x[i].y][game->x[i].x] = 'X';
        }
        i++;
    }
}
