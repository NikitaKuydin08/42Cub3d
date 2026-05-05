/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-04 11:35:37 by Nikita_Kuydin     #+#    #+#             */
/*   Updated: 2026-05-04 11:35:37 by Nikita_Kuydin    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int is_blank_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int rest_is_blank(char **file, int idx)
{
	int i;

	i = 0;
	while (file[idx] != NULL)
	{
		while (file[idx][i])
		{
			if (!ft_isspace(file[idx][i]))
				return (0);
			i++;
		}
		idx++;
	}
	return (1);
}

int	is_rgb_or_tex(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] <= 32)
		i++;
	if (ft_isprint(line[i]) && !ft_isdigit(line[i]))
	{
		if (ft_isprint(line[i + 1] && !ft_isdigit(line[i + 1])
			&& line[i + 2] <= 32))
			return (1);
		if ((line[i] == 'F' || line[i] == 'C')
			&& line[i + 1] <= 32)
			return (1);
	}
	return (0);
}

static char	*get_texture_value(char *line, int idx)
{
	
}

static int	store_texture(t_data *data, char *line)
{
	t_texrgbinfo	*info;
	int	i;

	i = 0;
	info = &data->texrgbinfo;
	while (line[i] && line[i] <= 32)
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && !info->north)
		info->north = get_texture_value(line, i + 2);
	else if (line[i] == 'S' && line[i + 1] == 'O' && !info->south)
		info->south = get_texture_value(line, i + 2);
	else if (line[i] == 'W' && line[i + 1] == 'E' && !info->west)
		info->west = get_texture_value(line, i + 2);
	else if (line[i] == 'E' && line[i + 1] == 'A' && !info->east)
		info->east = get_texture_value(line, i + 2);
	else if (line[i] == 'F' && !info->floor)
		info->floor = get_texture_value(line, i + 1);
	else if (line[i] == 'C' && !info->ceiling)
		info->ceiling = get_texture_value(line, i + 1);
	else
		return (print_err_msg(UNKNOWN_TEX));
	return (0);
}

static int	store_data(t_data *data, char *line)
{
	if (!data->map_started && is_rgb_or_tex(line))
		return (store_texture(data, line));
	data->map_started = true;
	data->map[data->map_idx] = ft_strdup(line);
	if (!data->map[data->map_idx])
		return (print_err_msg(ERR_MALLOC));
	data->map_idx++;
	return (0);
}

static int	finalize(t_data *data)
{
	t_texrgbinfo	*info;

	info = &data->texrgbinfo;
	data->map[data->map_idx] = NULL;
	if (!info->north || !info->south || !info->west || !info->east
		|| !info->ceiling || !info->floor)
		return (print_err_msg(MISSING_TEXTURE));
	if (data->map_idx == 0)
		return (print_err_msg(MISSING_MAP));
	return (0);
}

int extract_data_from_file(t_data *data, char **file)
{
	int             row;

	row = 0;
	data->map_idx = 0;
	data->map_started = false;
	while (row < data->line_count)
	{
		if (is_blank_line(data->file[row]))
		{
			if (data->map_started)
			{
				if (!rest_is_blank(data->file, row + 1))
					return (print_err_msg(MAP_NOT_LAST));
				break ;
			}
		}
		else if (store_data(data, data->file[row]))
			return (1);
		row++;
	}
	return (finalize(data));
}
