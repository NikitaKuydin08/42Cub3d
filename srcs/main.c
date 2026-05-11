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

// 	MLX_KEY_W				= 87,
//  MLX_KEY_A				= 65,
// 	MLX_KEY_D				= 68,
// 	MLX_KEY_S				= 83,
// 	MLX_KEY_ESCAPE			= 256,
// 	MLX_KEY_LEFT			= 263,
// 	MLX_KEY_RIGHT			= 262,
/*
THE map can only consist of 6 possible characters:
0 for an empty space
1 for a wall
N for spawning a player looking north
S for spawning a player looking south
E for spawning a player looking east
W for spawning a player looking west
*/

/*
	- Digital Differential Analysis (DDA) algorithm

Valid map is it has 
*/

// void	print_test_map(char **map)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (map[i])
// 	{
// 		j = 0;
// 		while (map[i][j])
// 		{
// 			printf("%c", map[i][j]);
// 			j++;
// 		}
// 		i++;
// 	}
// 	printf("\n");
// }

// EVERYWHERE the function returns 1 on failure

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
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (parsing(data, argv) != 0)
		return (0);
	init_data(data);
	init_mlx(data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	free(data);
	return (0);
}
