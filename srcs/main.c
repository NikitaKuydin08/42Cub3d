/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-04-24 09:48:17 by Nikita_Kuydin     #+#    #+#             */
/*   Updated: 2026-04-24 09:48:17 by Nikita_Kuydin    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// EVERYWHERE the function returns 1 on failure

void	start_game(t_data *data)
{
	// prep_player(data);
	data->mlx = mlx_init(data->win_width, data->win_height, "cub3d", false);
	if (!data->mlx)
	{
		ft_putstr_fd("data: Error: mlx: Could not initialize mlx", 2);
		ft_error(data, 1);
	}
	draw_game(data);
	mlx_key_hook(data->mlx, key_hook, data);
	mlx_loop_hook(data->mlx, loop_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	free(data);
}

int	parsing(t_data *data, char **argv)
{
	if (check_file(argv[1], true))
		ft_error(data, 0);
	if (map_copy_into_file(argv[1], data))
		ft_error(data, 0);
	if (extract_data_from_file(data))
		return (free_data(data));
	if (check_textures(&data->texrgbinfo))
		return (free_data(data));
	if (check_map(data))
		return (free_data(data));
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (print_err_msg(USAGE));
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (1);
	init_data(data);
	if (parsing(data, argv) != 0)
		return (0);
	start_game(data);
	return (0);
}
