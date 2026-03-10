/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 04:01:45 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/10 03:25:53 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int parse(t_game *game, char *av)
{
	int fd;

	if (!verif_map_extension(av))
		return (send_error("➜ invalid file"),1);
	/* fd = open(av, O_RDONLY);
	if (fd == -1)
		return (send_error("➜ fill won't open"), 1); */
	if (read_map(game))
		return (send_error("➜ invalid map"), 1);
	if (set_map(game))
	// stocker la carte dans game->map (tableau de chaînes),
	// compter les lignes (game->map_rows) et colonnes (game->map_cols),
	if (read_and_set_map_size(game, fd))
		return (close(fd),1);
	/* if (set_map(game, av, fd))
		return (close(fd),1); */
	// vérifier la validité de la carte (murs, joueur, collectibles, sortie),
	// et initialiser les positions du joueur, etc.
	
	// Fermer le fichier
	close(fd);
	
	// Retourner 0 en cas de succès
	return (0);
}

int verif_map_extension(char *s)
{
	int len;
	
	len = ft_strlen(s);
	if (len < 4)
		return (0);
	if(!(ft_strncmp(&s[len - 4], ".ber", 4)))
		return (1);
	return (0);
}

int read_and_set_map_size(t_game *game)
{
	char	*line;
	int		fd;
	
	line = get_next_line(fd);
	while (line)
	{
		if (game->map_rows == 1)
			game->map_cols = ft_strlen(line);
		else if ((int)ft_strlen(line) != game->map_cols)
			return (send_error("➜ Map file is empty"), 1);
		line = get_next_line(fd);
	}
	if (game->map_rows == 0)
		return (send_error("➜ Map file is empty"), 1);
	return (0);
}

int	set_map(t_game *game, char *av, int fd)
{
	char	*line;
	
	line = get_next_line(fd);
	while (line)
	{

	}
	return (0);
}