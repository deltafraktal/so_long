/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 06:35:10 by dgeara            #+#    #+#             */
/*   Updated: 2026/06/23 17:58:02 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long_bonus.h"

#ifdef __linux__

int	animation(t_game *game)
{
	game->delay++;
	game->frame_count++;
	if ((game->delay % 500) == 0)
	{
		move_x(game);
		game->delay = 0;
	}
	if ((game->delay % 4000) == 0)
	{
		render(game);
	}
	return (0);
}

/* int	animation(t_game *game)
{
	game->frame_count++;
	if (game->frame_count % X_SPEED == 0)
		move_x(game);
	render(game);
	return (0);
} */
#else

int	animation(t_game *game)
{
	game->frame_count++;
	if (game->frame_count % 25 == 0)
		move_x(game);
	render(game);
	return (0);
}

#endif

/* void	render_animation(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_rows)
	{
		x = 0;
		while (x < game->map_cols)
		{
			if (game->map[y][x] == 'C')
				put_img(game, game->tex.c[game->frame_count / 8 % 2], y, x);
			else if (game->map[y][x] == 'E' && game->c_left == 0)
				put_img(game, game->tex.e[game->frame_count / 3 % 3], y, x);
			x++;
		}
		y++;
	} 
}*/
