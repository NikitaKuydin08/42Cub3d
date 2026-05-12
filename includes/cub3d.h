/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-04-24 09:52:39 by Nikita_Kuydin     #+#    #+#             */
/*   Updated: 2026-04-24 09:52:39 by Nikita_Kuydin    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "../libft/includes/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdint.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>

// VARIABLES //
# define WIN_HEIGHT 800
# define WIN_WIDTH 800

// ERROR MESSAGES //
# define USAGE "Usage: ./cub3d <path/to/map.cub>"
# define FILE_NOT_EXIST "File doesn't exist"
# define FILE_NOT_REGULAR "File is not a regular file"
# define WRONG_FILE_EXT "FIle has wrong extension, not .cub"
# define WRONG_TEX_EXT "Not a .png file"
# define OPEN_FILE_ERR "Couldn't open the file, wrong permissions"
# define FILE_IS_EMPTY "File is empty"
# define ERR_MALLOC "Memory allocation error"
// INSIDE OF FILE ERROR //
# define MAP_NOT_LAST "Some content after map in the file"
# define MISSING_MAP "Map doesn't exist in the file"
# define MISSING_TEXTURE "At least one texture or rgb colours is missing"
# define UNKNOWN_TEX "Unknown texture identifier value"
# define DUPLICATE_TEX "Duplicate texture identifier"
# define BAD_TEX_VALUE "Bad texture value (missing, malloc fail, or \
trailing garbage)"
# define EXPECTED_WHITESPACE "Header identifier missing whitespace separator"
# define MISSED_TEX "At leaast one texture is missing"
# define INVALID_COUNT_RGB "Invalid number of rgb values, it must be exactly 3"
# define CONTAINS_OTHER_CHAR "At least one rgb colour contains non-digit \
char (including signs)"
# define OUT_OF_RANGE "At least one of R,G,B colours is out of range [0, 255]"
// MAPS_ERRORS //
# define WALL_HOLE_WEST "Map has a hole on the west"
# define WALL_HOLE_NORTH "Map has a hole on the north"
# define WALL_HOLE_SOUTH "Map has a hole on the south"
# define WALL_HOLE_EAST "Map has a hole on the east"
# define MAP_TOO_SMALL "Map is smaller than 3 lines"
# define WRONG_CHAR "Map composed of char(s) different from [0,1,N,S,E,W]"
# define MULTIPLE_PLAYER "Player's position appears in the map more than once"
# define NO_PLAYER "Map doesn't have player. Expected (N, S, E, or W)"
# define TRAPPED_PLAYER "Map doesn't have cell (0) next to player's position"
# define ERR_TAB "Tab character is not allowed in map, only spaces"

// STRUCTURES //
typedef struct s_texrgbinfo
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*floor;
	char	*ceiling;
	int		hex_floor;
	int		hex_ceiling;

}	t_texrgbinfo;

typedef struct s_player
{
	char	orientation;
	int		x;
	int		y;
	double	pos_x;
	double	pos_y;

}	t_player;

typedef struct s_data
{
	void			*mlx;
	void			*image;
	int				win_height;
	int				win_width;

	char			**file;
	char			*path;
	int				fd;
	int				line_count;

	char			**map;
	int				map_idx;
	int				map_line;
	bool			map_started;
	int				row_count;

	t_player		player;
	t_texrgbinfo	texrgbinfo;
}	t_data;

void	init_data(t_data *data);
void	init_mlx(t_data *cub3d);

// CHECK_MAP_CLOSURE //
int		check_closure(t_data *data, char **map);

// CHECK_MAP //
int		check_map(t_data *data);

// CHECK_TEXTURES //
int		check_textures(t_texrgbinfo *texinfo);
// EXTRACT_DATA //
int		extract_data_from_file(t_data *data);

// HELPERS_TO_EXTRACT //
int		finalize(t_data *data);
int		is_rgb_or_tex(char *line);
int		rest_is_blank(char **file, int idx);
int		is_blank_line(char *line);
char	**recognise_texture(t_texrgbinfo *info, char *line, int *i);

// MAP_COPY //
int		map_copy_into_file(char *arg, t_data *data);

// PERMISSION //
int		check_file(char *arg, bool cub);

// UTILS //
int		print_err_msg(char *msg);
void	ft_error(t_data *data, int exit_code);
int		free_data(t_data *data);
void	free_tab(char **tab);

#endif