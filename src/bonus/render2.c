/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 02:59:57 by dgeara            #+#    #+#             */
/*   Updated: 2026/06/23 17:58:02 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long_bonus.h"

void	*get_tile_img(t_game *game, char c)
{
	if (c == 'C')
		return (game->tex.c[game->frame_count / ALL_SPEED % 2]);
	if (c == 'E' && game->c_left > 0)
		return (game->tex.f);
	if (c == 'E' && game->c_left == 0)
		return (game->tex.e[game->frame_count / ALL_SPEED % 3]);
	if (c == 'P' || c == 'Z')
		return (game->tex.p[0]);
	if (c == '0')
		return (game->tex.f);
	if (c == 'X')
		return (game->tex.x[game->frame_count / ALL_SPEED % 3]);
	return (NULL);
}

void	put_img(t_game *g, void *img, int y, int x)
{
	int	screen_x;
	int	screen_y;

	screen_x = (x - g->cam_x) * TILE_SIZE;
	screen_y = (y - g->cam_y) * TILE_SIZE;
	if (screen_x < 0 || screen_y < 0)
		return ;
	if (screen_x >= g->view_w * TILE_SIZE)
		return ;
	if (screen_y >= g->view_h * TILE_SIZE)
		return ;
	mlx_put_image_to_window(g->mlx, g->win, img, screen_x, screen_y);
}
