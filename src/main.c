/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 04:21:29 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/19 19:14:14 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (send_error("➜ use ./so_long <map.ber>"), 1);
	init_game(&game);
	game.mlx = mlx_init();
	if (!game.mlx)
        return (send_error("➜ mlx not initialized"), 1);
	if (init_textures(&game))
		return (free_textures(&game), 1);
	if (parse(&game, av[1]))
		return (1);
	game.win = mlx_new_window(game.mlx, TILE_SIZE * game.map_cols, TILE_SIZE * game.map_rows, "so_loooong");
	if (!game.win)
    	return (send_error("➜ mlx new window failed"), 1);
	render_walls(&game);
	render(&game);
	mlx_hook(game.win, KEY_PRESS, KEY_PRESS_MASK, handle_keys, &game);
    mlx_hook(game.win, DESTROY_NOTIFY, NO_MASK, close_window, &game);
	mlx_loop_hook(game.mlx, animation, &game);
	mlx_loop(game.mlx);
	return (0);
}
