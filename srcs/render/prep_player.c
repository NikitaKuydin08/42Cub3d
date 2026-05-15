/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-15 04:06:50 by Nikita_Kuydin     #+#    #+#             */
/*   Updated: 2026-05-15 04:06:50 by Nikita_Kuydin    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	prep_player(t_data *data)
{
	t_player	*player;

	player = &data->player;
	player->pos_x = (double)player->x + 0.5;
	player->pos_y = (double)player->y + 0.5;
}
