/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:21:18 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/19 19:22:49 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"


void	render_walls(t_game *game)
{
	int y;
	int x;

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
	int y;
	int x;

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
	int y;
	int x;

	y = 1;
	while (y < game->map_rows - 1)
	{
		x = 1;
		while (x < game->map_cols - 1)
		{
			if (game->map[y][x] == 'C')
				put_img(game, game->tex.c[game->frame_count / 8 % 2], y, x);
			else if (game->map[y][x] == 'E' && game->c_count > 0)
				put_img(game, game->tex.f, y, x);
			else if (game->map[y][x] == 'E' && game->c_count == 0)
				put_img(game, game->tex.e[game->frame_count / 8 % 3], y, x);
			else if (game->map[y][x] == 'P')
				put_img(game, game->tex.p[0], y, x);
			else if (game->map[y][x] == '0')
				put_img(game, game->tex.f, y, x);
			else if (game->map[y][x] == 'Z')
				put_img(game, game->tex.pe, y, x);
			x++;
		}
		y++;
	}
}

void	put_img(t_game *g, void *img, int y, int x)
{
	mlx_put_image_to_window(g->mlx, g->win, img, x * TILE_SIZE, y * TILE_SIZE);
}

void render_moves_count(t_game *game)
{
	char	*str;
	int		i;
	int		x;
	
	str = ft_itoa(game->moves);
	i = 0;
	x = 23;
	while (str[i])
	{
		mlx_put_image_to_window(game->mlx, game->win,game->tex.d[str[i] - '0'], x, 8);
		x += 22;
		i++;
	}
	free(str);
}

void	render(t_game *game)
{
	if (game->won == 2)
        return ;
	/* render_background(game); */
	render_elements(game);
	render_moves_count(game);
}