/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_and_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 22:12:07 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/30 04:45:12 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

// verify the map is surrounded by wall
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

// verify there's the right number of elements and set player position
void	count_char(t_game *game, char c, int y, int x)
{
	if (c == 'P')
	{
		game->p_x = x;
		game->p_y = y;
		game->p_count++;
	}
	else if (c == 'X')
		game->x_count++;
	else if (c == 'E')
		game->e_count++;
	else if (c == 'C')
		game->c_count++;
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
			count_char(game, game->map[y][x], y, x);
			x++;
		}
		y++;
	}
	game->c_left = game->c_count;
	return (game->p_count == 1 && game->e_count == 1 && game->c_count >= 1);
}

// copy map for floodflill
int	copy_map(t_game *game, char ***cpy)
{
	int	i;

	i = 0;
	*cpy = malloc(sizeof(char *) * (game->map_rows + 1));
	if (!*cpy)
		return (0);
	while (i < game->map_rows)
	{
		(*cpy)[i] = strdup(game->map[i]);
		if (!(*cpy)[i])
			return (free_tab(*cpy, i), 0);
		i++;
	}
	(*cpy)[i] = NULL;
	return (1);
}

// fill cases reachable from player position with 'o'
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

// send divers checks
// verify if some elements haven't been reached
// pby floodfill and are still unreachable
int	validate_map(t_game *game)
{
	char	**cpy;
	int		y;
	int		x;

	y = 0;
	if (!check_walls(game))
		return (send_error("➜ invalid map walls"), 0);
	if (!count_elements(game))
		return (send_error("➜ invalid count of element"), 0);
	if (!copy_map(game, &cpy))
		return (send_error("➜ failled at copying map"), 0);
	flood_fill(cpy, game->p_y, game->p_x);
	while (cpy[y])
	{
		x = 0;
		while (cpy[y][x])
		{
			if (cpy[y][x] == 'C' || cpy[y][x] == 'E')
				return (send_error("➜ E or C unreachable"),
					free_tab(cpy, game->map_rows - 1), 0);
			x++;
		}
		y++;
	}
	return (free_tab(cpy, game->map_rows - 1), 1);
}
