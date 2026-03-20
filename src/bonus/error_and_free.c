/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:58:49 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/20 03:20:49 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

int	send_error(char *msg)
{
	ft_printf(BOLD PURPLE "Error\n"END YELLOW "%s\n" END, msg);
	return (1);
}

void	free_tab(char **tab, int i)
{
	if (!tab)
		return ;
	while (i >= 0)
		free (tab[i--]);
	free (tab);
}

void	destroy_enemies_img(t_game *game)
{
	short_destroy_image(game, game->tex.x[0]);
	short_destroy_image(game, game->tex.x[1]);
	short_destroy_image(game, game->tex.x[2]);
}

void	destroy_digits_img(t_game *game)
{
	short_destroy_image(game, game->tex.d[0]);
	short_destroy_image(game, game->tex.d[1]);
	short_destroy_image(game, game->tex.d[2]);
	short_destroy_image(game, game->tex.d[3]);
	short_destroy_image(game, game->tex.d[4]);
	short_destroy_image(game, game->tex.d[5]);
	short_destroy_image(game, game->tex.d[6]);
	short_destroy_image(game, game->tex.d[7]);
	short_destroy_image(game, game->tex.d[8]);
	short_destroy_image(game, game->tex.d[9]);
}

void	free_textures(t_game *game)
{
	if (!game || !game->mlx)
		return ;
	destroy_enemies_img(game);
	destroy_digits_img(game);
	short_destroy_image(game, game->tex.p[0]);
	short_destroy_image(game, game->tex.p[1]);
	short_destroy_image(game, game->tex.f);
	short_destroy_image(game, game->tex.w);
	short_destroy_image(game, game->tex.c[0]);
	short_destroy_image(game, game->tex.c[1]);
	short_destroy_image(game, game->tex.e[0]);
	short_destroy_image(game, game->tex.e[1]);
	short_destroy_image(game, game->tex.e[2]);
}

void	short_destroy_image(t_game *game, void *img)
{
	if (img)
		mlx_destroy_image(game->mlx, img);
}
