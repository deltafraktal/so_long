/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:21:18 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/19 16:08:47 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"


void	render_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_cols)
	{
		put_img(game, game->tex.w, 0, i);
		put_img(game, game->tex.w, game->map_rows - 1, i);
		i++;
	}
	i = 0;
	while (i < game->map_rows)
	{
		put_img(game, game->tex.w, i, 0);
		put_img(game, game->tex.w, i, game->map_cols - 1);
		i++;
	}
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
				put_img(game, game->tex.c[game->frame_count / 8 % 2], y, x);
			else if (game->map[y][x] == 'E' && game->c_count > 0)
				put_img(game, game->tex.f, y, x);
			else if (game->map[y][x] == 'E' && game->c_count == 0)
				put_img(game, game->tex.e[game->frame_count / 8 % 3], y, x);
			else if (game->map[y][x] == 'P')
				put_img(game, game->tex.p[0], y, x);
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

/* void render_moves(t_game *game)
{
	char    *str;

	str = ft_itoa(game->moves);
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFF0000, "moves:");
	mlx_string_put(game->mlx, game->win, 60, 20, 0xFF0000, str);
	free(str);
} */

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
	render_background(game);
	render_elements(game);
	render_moves_count(game);
}