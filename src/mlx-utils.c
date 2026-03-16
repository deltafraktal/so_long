/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx-utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:16:11 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/16 16:04:27 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	move_p(t_game *game, int x, int y)
{
	if (game->map[x][y] == '1')
		return (0);
	else if (game->map[x][y] == 'C')
		game->c_left--;
	else if (game->map[x][y] == 'E' && game->c_left == 0)
		return (/* >>> won(), */ 1);
	game->map[game->p_x][game->p_y] = '0';
	game->map[x][y] = 'P';
	game->p_x = x;
	game->p_y = y;
	game->moves++;
	/* >>> render function*/
}

int	handle_keys(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		move_p(game, game->p_x, game->p_y + 1);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		move_p(game, game->p_x, game->p_y - 1);
	else if (keycode == KEY_W || keycode == KEY_UP)
		move_p(game, 0, 1);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		move_p(game, 0, -1);
	return (0);
}
