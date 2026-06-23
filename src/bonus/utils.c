/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 22:16:11 by dgeara            #+#    #+#             */
/*   Updated: 2026/06/23 03:02:42 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

int	line_len(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	return (i);
}

char	*strdup_no_newline(const char *s1)
{
	char	*dup;
	int		i;

	dup = malloc(ft_strlen(s1) + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s1[i] && s1[i] != '\n')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	free_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

// fill cases reachable from player position with 'o'
void	flood_fill(char **cpy, int y, int x)
{
	if (cpy[y][x] == 'o' || cpy[y][x] == '1')
		return ;
	cpy[y][x] = 'o';
	flood_fill(cpy, y + 1, x);
	flood_fill(cpy, y - 1, x);
	flood_fill(cpy, y, x + 1);
	flood_fill(cpy, y, x - 1);
}
