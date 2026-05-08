/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-07 15:05:14 by Nikita_Kuydin     #+#    #+#             */
/*   Updated: 2026-05-07 15:05:14 by Nikita_Kuydin    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	We might want to change the extraction a little bit, so that the
	validation was a little easier.

	all function return 1 on failure
*/

static int  check_top_or_btm(char **map, int i, int j)
{
	// if (!map || !map[i] || !map[i][j])
	// 	return (1);
	while (map[i][j] && map[i][j] <= 32)
		j++;
	while (map[i][j] && map[i][j] > 32)
	{
		if (map[i][j] != '1')
			return (1);
		j++;
	}
	return (0);
}

static int  check_borders(t_data *data, char **map)
{
	int i;
	int j;

	if (check_top_or_btm(map, 0, 0))
		return (print_err_msg(WALL_HOLE_NORTH));
	i = 1;
	while (i < data->mapinfo.row_count - 1)
	{
		j = ft_strlen(map[i]);
		while (j > 0 && map[i][j] <= 32)
			j--;
		if (map[i][j] != '1')
			return (print_err_msg(WALL_HOLE_EAST));
		i++;
	}
	if (check_top_or_btm(map, i, 0))
		return (print_err_msg(WALL_HOLE_SOUTH));
	return (0);
}

int check_map(t_data *data)
{
	if (!data->map)
		return (print_err_msg(MISSING_MAP));
	if (check_borders(data, data->map))
		return (1);
	return (0);
}
