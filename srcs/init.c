/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-04-24 10:04:16 by Nikita_Kuydin     #+#    #+#             */
/*   Updated: 2026-04-24 10:04:16 by Nikita_Kuydin    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_error(t_data *data, int exit_code)
{
	if (!data)
		exit(exit_code);
	if (data->image && data->mlx)
		mlx_delete_image(data->mlx, data->image);
	if (data->mlx)
		mlx_close_window(data->mlx);
	// free_data(data); TODO
	exit(exit_code);
}

void	init_data(t_data *data)
{
	data->win_height = 800;
	data->win_width = 800;
}

void	init_mlx(t_data *cub3d)
{
	cub3d->mlx = mlx_init(cub3d->win_width, cub3d->win_height, "Cub3D", true);
	if (!cub3d->mlx)
	{
		ft_putstr_fd("cub3d: Error: mlx: Could not initialize mlx", 2);
		ft_error(cub3d, 1);
	}
	cub3d->image = mlx_new_image(cub3d->mlx, cub3d->win_width, cub3d->win_height);
	if (!cub3d->image)
	{
		ft_putstr_fd("cub3d: Error: mlx: Could not allocate a new image buffer", 2);
		ft_error(cub3d, 1);
	}
	if (mlx_image_to_window(cub3d->mlx, cub3d->image, 0, 0) < 0)
	{
		ft_putstr_fd("cub3d: Error: mlx: Could not draw a new image", 2);
		ft_error(cub3d, 1);
	}
}
