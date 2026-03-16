/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_and_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 22:12:07 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/16 16:07:37 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	check_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_cols)
	{
		if (game->map[0][i] != '1' || game->map[game->map_rows - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < game->map_rows)
	{
		if (game->map[i][0] != '1' || game->map[i][game->map_cols - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	count_elements(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'P')
			{
				game->p_x = x;
				game->p_y = y;
				game->p_count++;
			}
			else if (game->map[y][x] == 'E')
				game->e_count++;
			else if (game->map[y][x] == 'C')
				game->c_count++;
			x++;
		}
		y++;
	}
	return (game->p_count == 1 && game->e_count == 1 && game->c_count >= 1);
}

int	copy_map(t_game *game, char ***cpy)
{
	int	i;

	i = 0;
	cpy = malloc(sizeof(char *) * (game->map_rows + 1));
	if (!cpy)
		return (0);
	while (i < game->map_rows)
	{
		cpy[i] = strdup(game->map[i]);
		if (!cpy[i])
			return (free_tab(cpy, i), 0);
		i++;
	}
	cpy[i] = NULL;
	return (1);
}

void	flood_fill(char **cpy, int y, int x)
{
	if (cpy[y][x] == 'o' || cpy[y][x] == '1')
		return ;
	cpy[y][x] = 'o';
	flood_fill(cpy, y + 1, x);
	flood_fill(cpy, y - 1, x);
	flood_fill(cpy, y, x + 1);
	flood_fill(cpy, y, x - 1);
}

int	validate_map(t_game *game)
{
	char	**cpy;
	int		y;
	int		x;

	y = 0;
	if (!check_walls(game))
		return (0);
	if (!count_elements(game))
		return (0);
	if (!copy_map(game, &cpy))
		return (0);
	flood_fill(cpy, game->p_y, game->p_x);
	while (cpy[y])
	{
		x = 0;
		while (cpy[y][x])
		{
			if (cpy[y][x] == 'C' || cpy[y][x] == 'E')
				return (free_tab(cpy, game->map_rows - 1), 0);
			x++;
		}
		y++;
	}
	return (free_tab(cpy, game->map_rows - 1), 1);
}
