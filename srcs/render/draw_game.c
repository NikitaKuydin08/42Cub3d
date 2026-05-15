/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-15 07:19:25 by Nikita_Kuydin     #+#    #+#             */
/*   Updated: 2026-05-15 07:19:25 by Nikita_Kuydin    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_floor_n_ceiling(t_data *data)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	mid;

	mid = data->win_height / 2;
	(void)mid;
	y = 0;
	while (y < (uint32_t)data->win_height)
	{
		x = 0;
		while (x < (uint32_t)data->win_width)
		{
			if (y < mid)
				mlx_put_pixel(data->image, x, y,
					data->texrgbinfo.hex_ceiling);
			else
				mlx_put_pixel(data->image, x, y,
					data->texrgbinfo.hex_floor);
			x++;
		}
		y++;
	}
}

void	draw_game(t_data *data)
{
	data->image = mlx_new_image(data->mlx, data->win_width,
			data->win_height);
	if (!data->image)
	{
		ft_putstr_fd("data: Error: mlx: Could not allocate a new \
			image buffer", 2);
		ft_error(data, 1);
	}
	draw_floor_n_ceiling(data);
	// raycasting(data);
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) < 0)
	{
		ft_putstr_fd("data: Error: mlx: Could not draw a new image", 2);
		ft_error(data, 1);
	}
}
