/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 19:24:56 by nkuydin           #+#    #+#             */
/*   Updated: 2025/09/01 17:11:40 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	char	num[10];

	i = 0;
	if (n == 0)
		ft_putchar_fd('0', fd);
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		n = -n;
		ft_putchar_fd('-', fd);
	}
	while (n > 0)
	{
		num[i++] = n % 10 + '0';
		n = n / 10;
	}
	while (i > 0)
		ft_putchar_fd(num[--i], fd);
}
