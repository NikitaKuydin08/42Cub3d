/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 07:33:39 by nkuydin           #+#    #+#             */
/*   Updated: 2025/10/22 13:48:47 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printint(int nb)
{
	int		length;
	long	n;
	char	result;

	length = 0;
	n = (long) nb;
	if (n < 0)
	{
		length += write(1, "-", 1);
		n = -n;
	}
	if (n < 10)
	{
		result = n + '0';
		length += write(1, &result, 1);
	}
	if (n >= 10)
	{
		length += ft_printint(n / 10);
		length += ft_printint(n % 10);
	}
	return (length);
}
