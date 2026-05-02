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

static int	wrong_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len <= 4)
		return (1);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (1);
	return (0);
}

int	check_file(char **argv)
{
	char		*filename;
	int			fd;
	struct stat	path_stat;

	if (stat(argv[1], &path_stat) != 0)
		return (print_err_msg(FILE_NOT_EXIST));
	if (S_ISREG(path_stat.st_mode) == 0)
		return (print_err_msg(FILE_NOT_REGULAR));
	filename = argv[1];
	if (wrong_extension(filename))
		return (print_err_msg(WRONG_FILE_EXT));
	fd = open(filename, O_RDONLY);
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
