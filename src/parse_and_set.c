/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 04:01:45 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/30 04:42:13 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

// verify the map extension :P
int	verif_map_extension(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (len < 4)
		return (0);
	if (!(ft_strncmp(&s[len - 4], ".ber", 4)))
		return (1);
	return (0);
}

// verify theres no undesired char
int	check_char(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'P'
			&& line[i] != 'E' && line[i] != 'C' && line[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

//read, check chars,and that it is rectangle
int	read_map(t_game *game, char *av)
{
	int		fd;
	char	*line;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (send_error("➜ fill won't open"), 1);
	line = get_next_line(fd);
	if (!line)
		return (send_error("➜ empty map file"), close(fd), 0);
	game->map_cols = line_len(line);
	while (line)
	{
		if (check_char(line) || line_len(line) != game->map_cols)
			return (send_error("➜ invalid map"), free(line), close(fd), 0);
		game->map_rows++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

// set map and tab
int	set_map(t_game *game, char *av)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (send_error("➜ fill won't open"), 0);
	game->map = malloc(sizeof(char *) * (game->map_rows + 1));
	if (!game->map)
		return (close(fd), send_error("➜ malloc map failed"), 0);
	game->map[game->map_rows] = NULL;
	i = 0;
	line = get_next_line(fd);
	while (i < game->map_rows)
	{
		game->map[i] = strdup_no_newline(line);
		if (!game->map[i])
			return (send_error("➜ strdup failed"), free_tab(game->map, i - 1),
				free(line), close(fd), 0);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

// verify the map is valid, with a path from player to exit and collectibles
// and init player position etc
// return 0 if success
int	parse(t_game *game, char *av)
{
	if (!verif_map_extension(av))
		return (send_error("➜ invalid map extension"), 1);
	if (!read_map(game, av))
		return (1);
	if (!set_map(game, av))
		return (1);
	if (!validate_map(game))
		return (free_tab(game->map, game->map_rows - 1), 1);
	return (0);
}
