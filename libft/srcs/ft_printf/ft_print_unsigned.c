/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 08:37:15 by nkuydin           #+#    #+#             */
/*   Updated: 2025/10/22 13:48:32 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_unsigned(unsigned int nb)
{
	int		length;
	char	result;

	length = 0;
	if (nb < 10)
	{
		result = nb + '0';
		length += write(1, &result, 1);
	}
	if (nb >= 10)
	{
		length += ft_print_unsigned(nb / 10);
		length += ft_print_unsigned(nb % 10);
	}
	return (length);
}
