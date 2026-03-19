/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 06:35:10 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/19 18:50:31 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int animation(t_game *game)
{
    game->frame_count++;
    render(game);
    return (0);
}


void	render_animation(t_game *game)
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
			else if (game->map[y][x] == 'E' && game->c_count == 0)
				put_img(game, game->tex.e[game->frame_count / 3 % 3], y, x);
			x++;
		}
		y++;
	}
}
