/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 04:21:29 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/16 16:06:13 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"
#include "../minilibx_opengl_20191021-1/mlx.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (send_error("➜ use ./so_long <map.ber>"), 1);
	init_game(&game);
	parse(&game, av[1]);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, TILE_SIZE * game.map_cols, TILE_SIZE * game.map_rows, "so_loooong");
/* 	game.win = mlx_new_window(game.mlx, TILE_SIZE * 20, TILE_SIZE * 10, "so_loooong"); */
/* 	mlx_hook(game->win, KEY_PRESS, KEY_PRESS_MASK, handle_key, game);
    mlx_hook(game->win, DESTROY_NOTIFY, NO_MASK, close_window, game); */
	/* mlx_loop_hook(game.mlx, update_animation, &game); */
	/* mlx_loop(game.mlx); */
	return (0);
}
