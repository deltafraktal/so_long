/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:21:18 by dgeara            #+#    #+#             */
/*   Updated: 2026/06/23 17:58:02 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long_bonus.h"

void	render_walls(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_rows)
	{
		x = 0;
		while (x < game->map_cols)
		{
			if (game->map[y][x] == '1')
				put_img(game, game->tex.w, y, x);
			x++;
		}
		y++;
	}
	render_background(game);
}

void	render_background(t_game *game)
{
	int	y;
	int	x;

	y = 1;
	while (y < game->map_rows - 1)
	{
		x = 1;
		while (x < game->map_cols - 1)
		{
			if (game->map[y][x] == '0')
				put_img(game, game->tex.f, y, x);
			x++;
		}
		y++;
	}
}

void	render_elements(t_game *game)
{
	int		y;
	int		x;
	void	*img;

	y = 1;
	while (y < game->map_rows - 1)
	{
		x = 1;
		while (x < game->map_cols - 1)
		{
			img = get_tile_img(game, game->map[y][x]);
			if (img)
				put_img(game, img, y, x);
			x++;
		}
		y++;
	}
}

void	render_moves_count(t_game *g)
{
	char	*str;
	int		i;
	int		x;

	str = ft_itoa(g->moves);
	if (!str)
		return ;
	i = 0;
	x = 23;
	while (str[i])
	{
		mlx_put_image_to_window(g->mlx, g->win, g->tex.d[str[i] - '0'], x, 8);
		x += 22;
		i++;
	}
	free(str);
}

void	render(t_game *game)
{
	if (game->won == 2)
		return ;
	render_walls(game);
	render_elements(game);
	render_moves_count(game);
}
