/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 06:38:21 by dgeara            #+#    #+#             */
/*   Updated: 2026/03/15 17:50:24 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx.h"
# include "../minilibx_opengl_20191021-1/mlx.h"
# include "../minilibx-linux/mlx.h"
# include "../libft/inc/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# define BOLD "\033[1m"
# define PURPLE "\033[35m"
# define YELLOW "\033[33m"
# define END "\033[0m"

# define TILE_SIZE 64

# define DIR_DOWN 0
# define DIR_UP 1
# define DIR_LEFT 2
# define DIR_RIGHT 3

// MLX
// X11 Events
# define KEY_PRESS			2
# define DESTROY_NOTIFY		17

// X11 Masks
# define NO_MASK				0L
# define KEY_PRESS_MASK			(1L<<0)

// KEYS
# ifdef __linux__
#  define KEY_ESC    65307
#  define KEY_W      119
#  define KEY_A      97
#  define KEY_S      115
#  define KEY_D      100
#  define KEY_UP     65362
#  define KEY_DOWN   65364
#  define KEY_LEFT   65361
#  define KEY_RIGHT  65363
# else
#  define KEY_ESC    53
#  define KEY_W      13
#  define KEY_A      0
#  define KEY_S      1
#  define KEY_D      2
#  define KEY_UP     126
#  define KEY_DOWN   125
#  define KEY_LEFT   123
#  define KEY_RIGHT  124
# endif

typedef struct s_textures
{
	int		width;
	int		height;
	void	*player_l;
	void	*player_r;
	void	*player_d;
	void	*player_u;
	void	*floor;
	void	*wall;
	void	*collectible;
	void	*exit;
}			t_textures;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		*path;
	char		**map;
	int			map_rows;
	int			map_cols;
	int			p_count;
	int			e_count;
	int			c_count;
	int			c_left;
	int			p_x;
	int			p_y;
	int			moves;
	int			dir;
	t_textures  *textures;
}   t_game;

// function
// main
int		main(int ac, char **av);

//utils
int		send_error(char *msg);
int		line_len(char *line);
char	*strdup_no_newline(const char *s1);
int		check_char(char *line);

// parsing
int 	parse(t_game *game, char *av);
int 	verif_map_extension(char *s);
int 	read_map(t_game *game);
int 	set_map(t_game *game);

// init
int		init_game(t_game *game);

#endif