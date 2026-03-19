/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 22:12:07 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/19 01:47:38 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int init_textures(t_game *game)
{
    int     w;
    int     h;

    game->tex.p = mlx_xpm_file_to_image(game->mlx, "tex/p.xpm", &w, &h);
    game->tex.pe = mlx_xpm_file_to_image(game->mlx, "tex/pe.xpm", &w, &h);
    game->tex.f = mlx_xpm_file_to_image(game->mlx, "tex/f.xpm", &w, &h);
    game->tex.w = mlx_xpm_file_to_image(game->mlx, "tex/w.xpm", &w, &h);
    game->tex.c = mlx_xpm_file_to_image(game->mlx, "tex/c.xpm", &w, &h);
    game->tex.e = mlx_xpm_file_to_image(game->mlx, "tex/e.xpm", &w, &h);
    if (!game->tex.p || !game->tex.pe || !game->tex.f
        || !game->tex.w || !game->tex.c || !game->tex.e)
        return (send_error("➜ failed to load textures"), 1);
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
	game->dir = DIR_DOWN;
	return (0);
}
