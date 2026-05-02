/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:33:49 by nkuydin           #+#    #+#             */
/*   Updated: 2025/10/22 13:48:53 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printstat(unsigned long long stat, int c);

int	ft_printptr(unsigned long long ptr)
{
	int					length;

	length = 0;
	if (!ptr)
		length += ft_printstr("(nil)");
	else
	{
		length += ft_printstr("0x");
		length += ft_printstat(ptr, 'x');
	}
	return (length);
}

// static int	ft_printstat(unsigned long long stat, int c)
// {
// 	int		n;
// 	int		length;
// 	char	*str_stat[2];

// 	str_stat[0] = "0123456789abcdef";
// 	str_stat[1] = "0123456789ABCDEF";
// 	length = 0;
// 	if (c == 'x')
// 		n = 0;
// 	if (c == 'X')
// 		n = 1;
// 	if (stat < 0)
// 	{
// 		stat = -stat;
// 		length += write(1, "-", 1);
// 	}
// 	if (stat < 16)
// 		length += write(1, &str_stat[n][stat], 1);
// 	if (stat >= 16)
// 	{
// 		length += ft_printstat((stat / 16), c);
// 		length += write(1, &str_stat[n][(stat % 16)], 1);
// 	}
// 	return (length);
// }

static int	ft_printstat(unsigned long long stat, int c)
{
	int		length;
	char	*str_stat;

	length = 0;
	str_stat = "0123456789abcdef";
	if (stat < 16)
		length += write(1, &str_stat[stat], 1);
	if (stat >= 16)
	{
		length += ft_printstat((stat / 16), c);
		length += write(1, &str_stat[(stat % 16)], 1);
	}
	return (length);
}
