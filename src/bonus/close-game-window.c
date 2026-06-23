/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close-game-window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:16:11 by dgeara            #+#    #+#             */
/*   Updated: 2026/06/23 03:07:45 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

int	close_window(t_game *game)
{
	cleanup(game);
	exit(0);
	return (0);
}

#ifdef __linux__

int	cleanup(t_game *game)
{
	if (!game)
		return (0);
	free_textures(game);
	if (game->map)
		free_tab(game->map, game->map_rows - 1);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->x)
		free(game->x);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	return (0);
}

int	close_game(t_game *game)
{
	if (!game)
		return (0);
	free_textures(game);
	if (game->map)
		free_tab(game->map, game->map_rows - 1);
	if (game->x)
		free(game->x);
	if (game->end_img)
		mlx_destroy_image(game->mlx, game->end_img);
	if (game->win2)
		mlx_destroy_window(game->mlx, game->win2);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
	return (0);
}
#else

int	cleanup(t_game *game)
{
	if (!game)
		return (0);
	free_textures(game);
	if (game->map)
		free_tab(game->map, game->map_rows - 1);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->x)
		free(game->x);
	if (game->mlx)
		free(game->mlx);
	return (0);
}

int	close_game(t_game *game)
{
	if (!game)
		return (0);
	free_textures(game);
	if (game->map)
		free_tab(game->map, game->map_rows - 1);
	if (game->x)
		free(game->x);
	if (game->end_img)
		mlx_destroy_image(game->mlx, game->end_img);
	if (game->win2)
		mlx_destroy_window(game->mlx, game->win2);
	if (game->mlx)
		free(game->mlx);
	exit(0);
	return (0);
}

#endif
