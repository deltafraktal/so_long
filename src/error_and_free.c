/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:58:49 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/17 02:49:03 by dgeara           ###   ########.fr       */
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

int	free_map(t_game *game, int rows)
{
	(void)game;
	(void)rows;
	return (0);
}

void free_textures(t_game *game)
{
    if (!game || !game->mlx)
        return;
    if (game->tex.p)
        mlx_destroy_image(game->mlx, game->tex.p);
    if (game->tex.pe)
        mlx_destroy_image(game->mlx, game->tex.pe);
    if (game->tex.f)
        mlx_destroy_image(game->mlx, game->tex.f);
    if (game->tex.w)
        mlx_destroy_image(game->mlx, game->tex.w);
    if (game->tex.c)
        mlx_destroy_image(game->mlx, game->tex.c);
    if (game->tex.e)
        mlx_destroy_image(game->mlx, game->tex.e);
}
