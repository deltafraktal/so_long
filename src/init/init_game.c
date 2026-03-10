/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 22:12:07 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/10 02:21:55 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->path = NULL;
	game->map = NULL;
	game->map_rows = 0;
	game->map_cols = 0;
	game->c_total = 0;
	game->c_left = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->moves = 0;
	game->dir = DIR_DOWN;
	game->textures = NULL;
	return (0);
}