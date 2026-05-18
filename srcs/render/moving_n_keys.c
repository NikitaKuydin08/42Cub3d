/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_n_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-15 14:41:55 by Nikita_Kuydin     #+#    #+#             */
/*   Updated: 2026-05-15 14:41:55 by Nikita_Kuydin    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// 	MLX_KEY_W				= 87,
//  MLX_KEY_A				= 65,
// 	MLX_KEY_D				= 68,
// 	MLX_KEY_S				= 83,
// 	MLX_KEY_ESCAPE			= 256,
// 	MLX_KEY_LEFT			= 263,
// 	MLX_KEY_RIGHT			= 262,
//	MLX_KEY_DOWN			= 264,
//	MLX_KEY_UP				= 265,

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == 256 && keydata.action == 1)
		mlx_close_window(data->mlx);
	else if (keydata.key == 87 || keydata.key == 265)
		ft_move(data, 0);
	else if (keydata.key == 83 || keydata.key == 264)
		ft_move(data, 1);
	else if (keydata.key == 65)
		ft_move(data, 2);
	else if (keydata.key == 68)
		ft_move(data, 3);
	else if (keydata.key == 263)
		// view change left
	else if (keydata.key == 262)
		// view change right
	data->needs_redraw = true;
}

void	loop_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->needs_redraw)
	{
		draw_game(data);
		data->needs_redraw = false;
	}
}
