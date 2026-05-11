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

int	print_err_msg(char *msg)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("\n", 1);
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
