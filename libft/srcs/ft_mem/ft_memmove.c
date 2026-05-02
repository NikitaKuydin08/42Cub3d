/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:09:08 by nkuydin           #+#    #+#             */
/*   Updated: 2025/08/29 12:59:42 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void *src, unsigned int n)
{
	unsigned int	i;
	unsigned char	*dest_temp;
	unsigned char	*src_temp;

	i = 0;
	if (src == 0 && dest == 0)
		return (0);
	dest_temp = dest;
	src_temp = src;
	if (dest_temp > src_temp)
	{
		while (n-- > 0)
			dest_temp[n] = src_temp[n];
	}
	else
	{
		while (n > 0)
		{
			dest_temp[i] = src_temp[i];
			i++;
			n--;
		}
	}
	return (dest);
}
