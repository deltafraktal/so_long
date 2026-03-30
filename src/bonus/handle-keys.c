/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle-keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:16:11 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/30 04:49:33 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

int	move_p(t_game *game, int y, int x)
{
	if (game->map[y][x] == '1')
		return (0);
	else if (game->map[y][x] == 'C')
		ft_printf("c left : %d / %d\n", (--game->c_left), game->c_count);
	else if (game->map[y][x] == 'X')
		return (ft_printf("YOU DEAD !\n"), pop_up(game, 1), 0);
	else if (game->map[y][x] == 'E' && game->c_left == 0)
		return (ft_printf("YEEPEEEEE YOU WON !\n"), pop_up(game, 0), 0);
	if (game->map[game->p_y][game->p_x] == 'Z')
		game->map[game->p_y][game->p_x] = 'E';
	else
		game->map[game->p_y][game->p_x] = '0';
	if (game->map[y][x] == 'E')
		game->map[y][x] = 'Z';
	else
		game->map[y][x] = 'P';
	game->p_y = y;
	game->p_x = x;
	game->moves++;
	if (game->c_left == 0)
		game->won = 1;
	ft_printf("moves : %d\n", game->moves);
	return (1);
}

int	handle_keys(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	if (game->won == 2)
		return (0);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		move_p(game, game->p_y, game->p_x - 1);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		move_p(game, game->p_y, game->p_x + 1);
	else if (keycode == KEY_W || keycode == KEY_UP)
		move_p(game, game->p_y - 1, game->p_x);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		move_p(game, game->p_y + 1, game->p_x);
	update_camera(game);
	render(game);
	return (0);
}
