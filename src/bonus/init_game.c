/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 22:12:07 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/20 03:14:11 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

int	init_tex_digit(t_game *game)
{
	int	w;
	int	h;

	game->tex.d[0] = mlx_xpm_file_to_image(game->mlx, "tex/d0.xpm", &w, &h);
	game->tex.d[1] = mlx_xpm_file_to_image(game->mlx, "tex/d1.xpm", &w, &h);
	game->tex.d[2] = mlx_xpm_file_to_image(game->mlx, "tex/d2.xpm", &w, &h);
	game->tex.d[3] = mlx_xpm_file_to_image(game->mlx, "tex/d3.xpm", &w, &h);
	game->tex.d[4] = mlx_xpm_file_to_image(game->mlx, "tex/d4.xpm", &w, &h);
	game->tex.d[5] = mlx_xpm_file_to_image(game->mlx, "tex/d5.xpm", &w, &h);
	game->tex.d[6] = mlx_xpm_file_to_image(game->mlx, "tex/d6.xpm", &w, &h);
	game->tex.d[7] = mlx_xpm_file_to_image(game->mlx, "tex/d7.xpm", &w, &h);
	game->tex.d[8] = mlx_xpm_file_to_image(game->mlx, "tex/d8.xpm", &w, &h);
	game->tex.d[9] = mlx_xpm_file_to_image(game->mlx, "tex/d9.xpm", &w, &h);
	if (!game->tex.d[0] || !game->tex.d[1] || !game->tex.d[2]
		|| !game->tex.d[3] || !game->tex.d[4] || !game->tex.d[5]
		|| !game->tex.d[6] || !game->tex.d[7] || !game->tex.d[8]
		|| !game->tex.d[9])
		return (1);
	return (0);
}

int	init_tex_x(t_game *game)
{
	int	w;
	int	h;

	game->tex.x[0] = mlx_xpm_file_to_image(game->mlx, "tex/x0.xpm", &w, &h);
	game->tex.x[1] = mlx_xpm_file_to_image(game->mlx, "tex/x1.xpm", &w, &h);
	game->tex.x[2] = mlx_xpm_file_to_image(game->mlx, "tex/x2.xpm", &w, &h);
	if (!game->tex.x[0] || !game->tex.x[1] || !game->tex.x[2])
		return (1);
	return (0);
}

int	init_tex_elements(t_game *game)
{
	int	w;
	int	h;

	game->tex.p[0] = mlx_xpm_file_to_image(game->mlx, "tex/p1.xpm", &w, &h);
	game->tex.p[1] = mlx_xpm_file_to_image(game->mlx, "tex/p2.xpm", &w, &h);
	game->tex.f = mlx_xpm_file_to_image(game->mlx, "tex/f.xpm", &w, &h);
	game->tex.w = mlx_xpm_file_to_image(game->mlx, "tex/w.xpm", &w, &h);
	game->tex.c[0] = mlx_xpm_file_to_image(game->mlx, "tex/c1.xpm", &w, &h);
	game->tex.c[1] = mlx_xpm_file_to_image(game->mlx, "tex/c2.xpm", &w, &h);
	game->tex.e[0] = mlx_xpm_file_to_image(game->mlx, "tex/e0.xpm", &w, &h);
	game->tex.e[1] = mlx_xpm_file_to_image(game->mlx, "tex/e1.xpm", &w, &h);
	game->tex.e[2] = mlx_xpm_file_to_image(game->mlx, "tex/e2.xpm", &w, &h);
	if (!game->tex.p[0] || !game->tex.p[1] || !game->tex.f
		|| !game->tex.w || !game->tex.c[0] || !game->tex.c[1]
		|| !game->tex.e[0] || !game->tex.e[1] || !game->tex.e[2])
		return (1);
	return (0);
}

int	init_textures(t_game *game)
{
	if (init_tex_digit(game))
		return (send_error("➜ failed to load digit textures"), 1);
	if (init_tex_x(game))
		return (send_error("➜ failed to load enemies texture"), 1);
	if (init_tex_elements(game))
		return (send_error("➜ failed to load elements texture"), 1);
	return (0);
}

int	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map = NULL;
	game->map_rows = 0;
	game->map_cols = 0;
	game->p_count = 0;
	game->e_count = 0;
	game->c_count = 0;
	game->c_left = 0;
	game->p_x = 0;
	game->p_y = 0;
	game->moves = 0;
	game->won = 0;
	game->frame_count = 0;
	ft_memset(&game->tex, 0, sizeof(t_tex));
	return (0);
}
