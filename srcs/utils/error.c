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

int print_err_msg(char *msg)
{
	ft_putstr_fd("Error", 2);
	ft_putstr_fd(msg, 2);
	return (1);
}
