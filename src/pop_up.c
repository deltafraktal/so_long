/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:22:39 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/19 19:45:00 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	pop_up(t_game *game, int dead)
{
	void    *win2;
    void    *img;
    int     w;
    int     h;

	game->won = 2; 
	if (!dead)
    	img = mlx_xpm_file_to_image(game->mlx, "tex/life.xpm", &w, &h);
	else
		img = mlx_xpm_file_to_image(game->mlx, "tex/death.xpm", &w, &h);
    if (!img)
        return (close_window(game, 1), 1);
	mlx_destroy_window(game->mlx, game->win);
    win2 = mlx_new_window(game->mlx, w, h, "YOU WON !");
    if (!win2)
        return (1);
	mlx_put_image_to_window(game->mlx, win2, img, 0, 0);
    mlx_hook(win2, DESTROY_NOTIFY, NO_MASK, close_game, game);
    mlx_key_hook(win2, handle_esc, game);
    return (0);
}

int	handle_esc(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	return (0);
}