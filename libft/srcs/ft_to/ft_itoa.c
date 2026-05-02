/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:15:43 by nkuydin           #+#    #+#             */
/*   Updated: 2025/09/01 20:43:35 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	counter(long nb);

char	*ft_itoa(int n)
{
	char	*buff;
	int		length;
	long	nb;

	nb = n;
	length = counter(nb);
	buff = (char *)malloc(sizeof(char) * (length + 1));
	if (!buff)
		return (0);
	buff[length] = '\0';
	if (nb < 0)
	{
		buff[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		buff[0] = '0';
	while (nb != 0)
	{
		buff[--length] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (buff);
}

static int	counter(long nb)
{
	int	count;

	count = 0;
	if (nb < 0)
	{
		count++;
		nb = -nb;
	}
	if (nb == 0)
		count++;
	while (nb != 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}
