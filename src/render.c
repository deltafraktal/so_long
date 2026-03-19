/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:21:18 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/19 02:07:00 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	render_background(t_game *game)
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
			else if (game->map[y][x] == '0')
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

	y = 0;
	while (y < game->map_rows)
	{
		x = 0;
		while (x < game->map_cols)
		{
			if (game->map[y][x] == 'C')
				put_img(game, game->tex.c, y, x);
			else if (game->map[y][x] == 'E')
				put_img(game, game->tex.e, y, x);
			else if (game->map[y][x] == 'P')
				put_img(game, game->tex.p, y, x);
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

void render_moves(t_game *game)
{
    char    *str;

    str = ft_itoa(game->moves);
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, "moves:");
    mlx_string_put(game->mlx, game->win, 60, 20, 0xFFFFFF, str);
    free(str);
}

void	render(t_game *game)
{
	render_background(game);
	render_elements(game);
	render_moves(game);
}

/* OLD SHIT */
/* void render_tile(t_game *game, int y, int x)
{
	if (game->map[y][x] == '1')
		
}

void render(t_game *game)
{
	int y;
	int x;

	y = 0;
	while (y < game->map_rows)
	{
		x = 0;
		while (x < game->map_cols)
		{
			render_tile(game, y, x);
			x++;
		}
		y++;
	}
} */