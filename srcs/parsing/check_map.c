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

	for the checking map closure, it might be just more logical to create a check
	got each 

	check_element needs to be changed to handle some small case - if map
	doesn't have a '0' in it - map failure

	i was thinking of checking player's position inside of check_cell,
	but we had a segmentation fault, because of the index going out of
	bounds of map
*/

static int	check_player_position(t_data *data, char **map)
{
	int	i;
	int	j;

	i = data->player.y;
	j = data->player.x;
	if (map[i - 1][j] == '0')
		return (0);
	if (map[i + 1][j] == '0')
		return (0);
	if (map[i][j - 1] == '0')
		return (0);
	if (map[i][j + 1] == '0')
		return (0);
	return (print_err_msg(TRAPPED_PLAYER));
}

static int	check_cell(t_data *data, char **map, int i, int j)
{
	if (!ft_strchr("01NSEW", map[i][j]))
		return (print_err_msg(WRONG_CHAR));
	if (ft_strchr("NSEW", map[i][j]))
	{
		if (data->player.orientation != '0')
			return (print_err_msg(MULTIPLE_PLAYER));
		data->player.orientation = map[i][j];
		data->player.x = j;
		data->player.y = i;
	}
	return (0);
}

static int	check_elements(t_data *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->mapinfo.row_count)
	{
		j = 0;
		while (map[i][j])
		{
			while (map[i][j] && map[i][j] <= 32)
				j++;
			if (map[i][j] == '\0')
				break ;
			if (check_cell(data, map, i, j))
				return (1);
			j++;
		}
		i++;
	}
	if (data->player.orientation == '0')
		return (print_err_msg(NO_PLAYER));
	return (0);
}

int	check_map(t_data *data)
{
	data->player.orientation = '0';
	if (!data->map)
		return (print_err_msg(MISSING_MAP));
	if (data->mapinfo.row_count < 3)
		return (print_err_msg(MAP_TOO_SMALL));
	if (check_elements(data, data->map))
		return (1);
	if (check_closure(data, data->map))
		return (1);
	if (check_player_position(data, data->map))
		return (1);
	return (0);
}
