/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-02 07:12:57 by Nikita_Kuydin     #+#    #+#             */
/*   Updated: 2026-05-02 07:12:57 by Nikita_Kuydin    ###   ########.fr       */
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

int print_err_msg(char *msg)
{
	ft_putstr_fd("Error", 2);
	ft_putstr_fd(msg, 2);
	return (1);
}

void	ft_error(t_data *data, int exit_code)
{
	if (!data)
		exit(exit_code);
	if (data->image && data->mlx)
		mlx_delete_image(data->mlx, data->image);
	if (data->mlx)
		mlx_close_window(data->mlx);
	free_data(data);
	exit(exit_code);
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

void	free_texinfo(t_texrgbinfo texinfo)
{
	
}

int	free_data(t_data *data)
{
	free_map(data);
	free_texinfo(data->texrgbinfo);
	return (1);
}