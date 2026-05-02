/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 03:32:16 by nkuydin           #+#    #+#             */
/*   Updated: 2025/10/22 13:48:57 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printstr(char *str)
{
	int	length;

	length = 0;
	if (!str)
		return (ft_printstr("(null)"));
	while (*str)
	{
		write(1, (str++), 1);
		length++;
	}
	return (length);
}
