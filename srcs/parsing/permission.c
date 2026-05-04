/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permission.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-02 05:24:27 by Nikita_Kuydin     #+#    #+#             */
/*   Updated: 2026-05-02 05:24:27 by Nikita_Kuydin    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	- bool cub used to determinee what type of file have been passed
	- checkfile function checks if the file has read permissions,
	not empty, not a directory. 
*/

static int	wrong_cub(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len <= 4)
		return (1);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (1);
	return (0);
}

static int	wrong_png(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len <= 4)
		return (1);
	if (ft_strncmp(filename + len - 4, ".png", 4) != 0)
		return (1);
	return (0);
}

int	check_file(char *arg, bool cub)
{
	int			fd;
	struct stat	path_stat;

	if (stat(arg, &path_stat) != 0)
		return (print_err_msg(FILE_NOT_EXIST));
	if (S_ISREG(path_stat.st_mode) == 0)
		return (print_err_msg(FILE_NOT_REGULAR));
	if (cub && wrong_cub(arg))
		return (print_err_msg(WRONG_FILE_EXT));
	if (!cub && wrong_png(arg))
		return (print_err_msg(WRONG_TEX_EXT));
	fd = open(arg, O_RDONLY);
	if (fd < 0)
		return (print_err_msg(OPEN_FILE_ERR));
	if (path_stat.st_size == 0)
	{
		close(fd);
		return (print_err_msg(FILE_IS_EMPTY));
	}
	close(fd);
	return (0);
}
