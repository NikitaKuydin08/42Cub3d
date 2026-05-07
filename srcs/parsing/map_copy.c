/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_filling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-04 09:39:51 by Nikita_Kuydin     #+#    #+#             */
/*   Updated: 2026-05-04 09:39:51 by Nikita_Kuydin    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	**Subject to change the name**
	- number of lines in the file
	- path to the file .cub
	- file[i][j] this is the copy of the file .cub, instead
	of accessing the file through fd each time, can be accessed
	by refering to data->file
	- have fd open at the time of copying, but we close it in the end
	of the function (file to map).

	copy - 
	read a line, allocate a memory for this line in the file[row];
	write the line into file[row], terminate with '\0';
	read the next line.
*/

static void	free_copy(char **copy)
{
	int	i;

	i = 0;
	while (copy[i])
	{
		free(copy[i]);
		i++;
	}
	if (copy)
	{
		free(copy);
		copy = NULL;
	}
}

static int	count_lines(char *path)
{
	int		count;
	char	*line;
	int		fd;

	count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (print_err_msg(OPEN_FILE_ERR));
	line = get_next_line(fd);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

static int	copy_file(int row, int column, int i, t_data *data)
{
	char	*line;

	line = get_next_line(data->fd);
	while (line != NULL)
	{
		i = 0;
		column = 0;
		data->file[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char *));
		if (!data->file[row])
		{
			free_copy(data->file);
			free(line);
			return (print_err_msg(ERR_MALLOC));
		}
		while (line[i])
			data->file[row][column++] = line[i++];
		data->file[row][column] = '\0';
		row++;
		free(line);
		line = get_next_line(data->fd);
	}
	data->file[row] = NULL;
	return (0);
}

int	map_copy_into_file(char *arg, t_data *data)
{
	int	row;
	int	column;
	int	i;

	i = 0;
	row = 0;
	column = 0;
	data->line_count = count_lines(arg);
	data->path = arg;
	data->file = ft_calloc(data->line_count + 1, sizeof(char *));
	if (!data->file)
		return (print_err_msg(ERR_MALLOC));
	data->fd = open(data->path, O_RDONLY);
	if (data->fd < 0)
		return (print_err_msg(strerror(errno)));
	else
	{
		copy_file(row, column, i, data);
		close(data->fd);
	}
	return (0);
}
