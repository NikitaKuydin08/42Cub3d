/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-08 10:34:37 by Nikita_Kuydin     #+#    #+#             */
/*   Updated: 2026-05-08 10:34:37 by Nikita_Kuydin    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

void	free_map(t_data *data)
{
	if (data->map)
		free_tab(data->map);
	if (data->file)
		free_tab(data->file);
	if (data->fd > 0)
		close(data->fd);
}

void	free_texinfo(t_texrgbinfo *textures)
{
	if (textures->north)
		free(textures->north);
	if (textures->south)
		free(textures->south);
	if (textures->west)
		free(textures->west);
	if (textures->east)
		free(textures->east);
	if (textures->ceiling)
		free(textures->ceiling);
	if (textures->floor)
		free(textures->floor);
}

int	free_data(t_data *data)
{
	free_map(data);
	free_texinfo(&data->texrgbinfo);
	free(data);
	return (1);
}
