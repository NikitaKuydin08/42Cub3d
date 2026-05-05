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

// ERROR MESSAGES //
# define USAGE "Usage: ./cub3d <path/to/map.cub>"
# define FILE_NOT_EXIST "File doesn't exist"
# define FILE_NOT_REGULAR "File is not a regular file"
# define WRONG_FILE_EXT "FIle has wrong extension, not .cub"
# define WRONG_TEX_EXT "Not a .png file"
# define OPEN_FILE_ERR "Couldn't open the file, wrong permissions"
# define FILE_IS_EMPTY "File is empty"
# define ERR_MALLOC "Memory allocation error"
# define MAP_NOT_LAST "Some content after map in the file"
# define MISSING_MAP "Map doesn't exist in the file"
# define MISSING_TEXTURE "At least one texture or rgb colours is missing"
# define UNKNOWN_TEX "Unknown texture value"

typedef	struct s_texrgbinfo
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		*floor;
	int		*ceiling;
	int		hex_floor;
	int		hex_ceiling;


}	t_texrgbinfo;

typedef struct	s_data
{
	void	*mlx;
	void	*image;
	int		win_height;
	int		win_width;

	char	**file;
	char	*path;
	int		fd;
	int		line_count;

	char	**map;
	int		map_idx;
	int		map_line;
	bool	map_started;

	t_texrgbinfo	texrgbinfo;
}	t_data;

void	init_data(t_data *data);
void	init_mlx(t_data *cub3d);

void	ft_error(t_data *data, int exit_code);

// VALIDATION //
int	check_file(char *arg, bool cub);
int	parsing(t_data *data, char **argv);

int	map_copy_into_file(char *arg, t_data *data);

// UTILS //
int print_err_msg(char *msg);


#endif