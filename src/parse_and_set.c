/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 04:01:45 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/16 16:11:30 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

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
	return (1);
}

//li, check les char, et que c'est bien un rectangle
int	read_map(t_game *game)
{
	int		fd;
	char	*line;

	fd = open(game->path, O_RDONLY);
	if (fd == -1)
		return (send_error("➜ fill won't open"), 1);
	line = get_next_line(fd);
	game->map_cols = line_len(line);
	while (line)
	{
		if (check_char(line))
			return (1);
		if (line_len(line) != game->map_cols)
			return (1);
		game->map_rows++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

//set la map en tableau
int	set_map(t_game *game)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(game->path, O_RDONLY);
	if (fd == -1)
		return (send_error("➜ fill won't open"), 1);
	game->map = malloc(sizeof(char *) * (game->map_rows + 1));
	if (!game->map)
		return (close(fd), send_error("➜ Malloc map failed"), 1);
	game->map[game->map_rows] = NULL;
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		game->map[i++] = strdup_no_newline(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	parse(t_game *game, char *av)
{
	if (!verif_map_extension(av))
		return (send_error("➜ invalid file"), 1);
	if (read_map(game))
		return (send_error("➜ invalid map"), 1);
	if (set_map(game))
		return (1);
	if (!validate_map(game) || !check_path(game))
		return (free_map(game, game->map_rows - 1), 1);
	// vérifier la validité de la carte (murs, joueur, collectibles, sortie),
	// et initialiser les positions du joueur, etc.
	
	// Fermer le fichier
	
	// Retourner 0 en cas de succès
	return (0);
}
