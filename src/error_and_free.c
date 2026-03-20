/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:58:49 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/20 03:53:24 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

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

void	free_textures(t_game *game)
{
	if (!game || !game->mlx)
		return ;
	short_destroy_image(game, game->tex.p);
	short_destroy_image(game, game->tex.f);
	short_destroy_image(game, game->tex.w);
	short_destroy_image(game, game->tex.c);
	short_destroy_image(game, game->tex.e);
}

void	short_destroy_image(t_game *game, void *img)
{
	if (img)
		mlx_destroy_image(game->mlx, img);
}
