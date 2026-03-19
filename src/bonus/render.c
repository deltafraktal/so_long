/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:21:18 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/20 00:13:51 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"


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

void *get_tile_img(t_game *game, char c)
{
	if (c == 'C') 
		return (game->tex.c[game->frame_count / 20 % 2]);
	if (c == 'E' && game->c_count > 0) 
		return (game->tex.f);
	if (c == 'E' && game->c_count == 0) 
		return (game->tex.e[game->frame_count / 20 % 3]);
	if (c == 'P' || c == 'Z') 
		return (game->tex.p[0]);
	if (c == '0') 
		return (game->tex.f);
	if (c == 'X') 
		return (game->tex.x[game->frame_count / 20 % 5]);
	return (NULL);
}

void	render_elements(t_game *game)
{
	int 	y;
	int 	x;
	void	*img;

	y = 1;
	while (y < game->map_rows - 1)
	{
		x = 1;
		while (x < game->map_cols - 1)
		{
			img = get_tile_img(game, game->map[y][x]);
			if (img)
				put_img(game, img, y , x);
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
