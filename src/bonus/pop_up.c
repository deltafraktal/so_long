/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:22:39 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/30 05:12:42 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

int	pop_up(t_game *g, int dead)
{
	int		w;
	int		h;

	g->won = 2;
	if (!dead)
		g->end_img = mlx_xpm_file_to_image(g->mlx, "tex/LIFE.xpm", &w, &h);
	else
		g->end_img = mlx_xpm_file_to_image(g->mlx, "tex/DEATH.xpm", &w, &h);
	if (!g->end_img)
		return (close_window(g), 1);
	mlx_destroy_window(g->mlx, g->win);
	g->win2 = mlx_new_window(g->mlx, w, h, "THE END");
	if (!g->win2)
		return (mlx_destroy_image(g->mlx, g->end_img), 1);
	mlx_put_image_to_window(g->mlx, g->win2, g->end_img, 0, 0);
	mlx_hook(g->win2, DESTROY_NOTIFY, NO_MASK, close_game, g);
	mlx_key_hook(g->win2, handle_esc, g);
	return (0);
}

int	handle_esc(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	return (0);
}
