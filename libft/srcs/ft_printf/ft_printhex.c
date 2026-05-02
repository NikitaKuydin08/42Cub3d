/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 09:46:04 by nkuydin           #+#    #+#             */
/*   Updated: 2025/10/22 13:48:42 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	ft_printhex(unsigned int hex, int c)
// {
// 	int		n;
// 	int		length;
// 	char	*str_hex[2];

// 	str_hex[0] = "0123456789abcdef";
// 	str_hex[1] = "0123456789ABCDEF";
// 	length = 0;
// 	if (c == 'x')
// 		n = 0;
// 	if (c == 'X')
// 		n = 1;
// 	if (hex < 16)
// 		length += write(1, &str_hex[n][hex], 1);
// 	if (hex >= 16)
// 	{
// 		length += ft_printhex((hex / 16), c);
// 		length += write(1, &str_hex[n][(hex % 16)], 1);
// 	}
// 	return (length);
// }

int	ft_printhex(unsigned int hex, int c)
{
	int		length;
	char	*str_hex;

	length = 0;
	if (c == 'x')
		str_hex = "0123456789abcdef";
	if (c == 'X')
		str_hex = "0123456789ABCDEF";
	if (hex < 16)
		length += write(1, &str_hex[hex], 1);
	if (hex >= 16)
	{
		length += ft_printhex((hex / 16), c);
		length += write(1, &str_hex[(hex % 16)], 1);
	}
	return (length);
}
