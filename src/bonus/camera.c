/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 00:54:59 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/20 03:48:21 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

void	update_camera(t_game *game)
{
	game->cam_x = game->p_x - game->view_w / 2;
	game->cam_y = game->p_y - game->view_h / 2;
	if (game->cam_x < 0)
		game->cam_x = 0;
	if (game->cam_y < 0)
		game->cam_y = 0;
	if (game->cam_x > game->map_cols - game->view_w)
		game->cam_x = game->map_cols - game->view_w;
	if (game->cam_y > game->map_rows - game->view_h)
		game->cam_y = game->map_rows - game->view_h;
}
