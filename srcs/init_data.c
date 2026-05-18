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

void	init_textures(t_texrgbinfo *texinfo)
{
	texinfo->north = NULL;
	texinfo->south = NULL;
	texinfo->east = NULL;
	texinfo->west = NULL;
	texinfo->floor = NULL;
	texinfo->ceiling = NULL;
	texinfo->hex_ceiling = 0;
	texinfo->hex_floor = 0;
}

void	init_player(t_player *player)
{
	player->orientation = '0';
	player->x = 0;
	player->y = 0;
	player->pos_x = 0.0;
	player->pos_y = 0.0;
}

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->image = NULL;
	data->win_height = WIN_HEIGHT;
	data->win_width = WIN_WIDTH;
	data->file = NULL;
	data->path = NULL;
	data->fd = 0;
	data->line_count = 0;
	data->map = NULL;
	data->map_idx = 0;
	data->map_line = 0;
	data->map_started = false;
	data->row_count = 0;
	data->needs_redraw = false;
	init_textures(&data->texrgbinfo);
	init_player(&data->player);
}
