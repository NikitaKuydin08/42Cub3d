/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helps_to_extract.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-07 14:45:48 by Nikita_Kuydin     #+#    #+#             */
/*   Updated: 2026-05-07 14:45:48 by Nikita_Kuydin    ###   ########.fr       */
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

	while (file[idx] != NULL)
	{
		i = 0;
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
	while (line[i])
	{
		if (!ft_strchr("01 \tNSEW\r\n", line[i]))
			return (1);
		i++;
	}
	return (0);
}

int	finalize(t_data *data)
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
