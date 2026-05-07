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

/*
	Memory needs to be allocated for the map, before storing anything
	in data->map[][]

	The storing needs to be refactored, because right now our
	error messages are fucked up. 
	Added recognise_texture that gives a store_texture an opportunity to
	recognise the unknown identifier, duplicate identifier and storing of
	the texture. 

	The recognise texture fixed a lot of problems. Although there is another
	thing right now. Sooo, NOassets/bluestone.xpm this one fails the
	is_rgb_or_tex check, and falls into the map storing, after successfull storing
	The check sees the the empty line, looks into the leftover, and finds out
	there is some stuff after the map he thinks he stored. I don't know. The
	is_rgb_or_tex function needs to make sure he checks everything before 
	saying that the current line is the map's line.
*/

static char	*get_texture_value(char *line, int idx)
{
	int		i;
	int		len;
	char	*res;

	len = 0;
	i = 0;
	while (line[idx] && line[idx] <= 32)
		idx++;
	len = idx;
	while(line[len] && line[len] > 32)
		len++;
	res = ft_calloc(len - idx + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (line[idx] && line[idx] > 32)
		res[i++] = line[idx++];
	res[i] = '\0';
	while(line[idx] && line[idx] <= 32)
		idx++;
	if (line[idx])
	{
		free(res);
		res = NULL;
	}
	return (res);
}

static char	**recognise_texture(t_texrgbinfo *info, char *line, int *i)
{
	char	**slot;
	int		idx;

	idx = *i;
	slot = NULL;
	while (line[idx] && line[idx] <= 32)
		idx++;
	if (line[idx] == 'N' && line[idx + 1] == 'O')
		slot = &info->north;
	else if (line[idx] == 'S' && line[idx + 1] == 'O')
		slot = &info->south;
	else if (line[idx] == 'W' && line[idx + 1] == 'E')
		slot = &info->west;
	else if (line[idx] == 'E' && line[idx + 1] == 'A')
		slot = &info->east;
	else if (line[idx] == 'F')
		slot = &info->floor;
	else if (line[idx] == 'C')
		slot = &info->ceiling;
	if (slot && (line[idx] == 'F' || line[idx] == 'C'))
		*i = idx + 1;
	else if (slot)
		*i = idx + 2;
	return (slot);
}

static int	store_texture(t_data *data, char *line)
{
	t_texrgbinfo	*info;
	char			**slot;
	int	i;

	i = 0;
	info = &data->texrgbinfo;
	while (line[i] && line[i] <= 32)
		i++;
	slot = recognise_texture(info, line, &i);
	if (!slot)
		return (print_err_msg(UNKNOWN_TEX));
	if (*slot)
		return (print_err_msg(DUPLICATE_TEX));
	if (line[i] && line[i] > 32)
		return (print_err_msg(EXPECTED_WHITESPACE));
	*slot = get_texture_value(line, i);
	if (!*slot)
		return (print_err_msg(BAD_TEX_VALUE));
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

int extract_data_from_file(t_data *data)
{
	int	row;

	row = 0;
	data->map_idx = 0;
	data->map_started = false;
	data->map = ft_calloc(data->line_count + 1, sizeof(char *));
	if (!data->map)
		return (print_err_msg(ERR_MALLOC));
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
