/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:58:49 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/30 04:16:51 by dgeara           ###   ########.fr       */
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
