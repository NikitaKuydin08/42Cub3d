/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_closure.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-11 09:40:52 by Nikita_Kuydin     #+#    #+#             */
/*   Updated: 2026-05-11 09:40:52 by Nikita_Kuydin    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_open(t_data *data, int i, int j)
{
	int	len;

	if (i < 0 || i >= data->row_count)
		return (1);
	len = ft_strlen(data->map[i]);
	if (j < 0 || j >= len)
		return (1);
	if (data->map[i][j] <= 32)
		return (1);
	return (0);
}

static int	check_neighbor(t_data *data, int i, int j)
{
	if (is_open(data, i - 1, j))
		return (print_err_msg(WALL_HOLE_NORTH));
	if (is_open(data, i + 1, j))
		return (print_err_msg(WALL_HOLE_SOUTH));
	if (is_open(data, i, j - 1))
		return (print_err_msg(WALL_HOLE_WEST));
	if (is_open(data, i, j + 1))
		return (print_err_msg(WALL_HOLE_EAST));
	return (0);
}

int	check_closure(t_data *data, char **map)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (i < data->row_count)
	{
		j = 0;
		len = ft_strlen(map[i]);
		while (j < len)
		{
			if (ft_strchr("0NSEW", map[i][j])
				&& check_neighbor(data, i, j))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
