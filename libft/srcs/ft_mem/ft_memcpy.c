/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:23:09 by nkuydin           #+#    #+#             */
/*   Updated: 2025/08/29 23:18:08 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest_temp;
	unsigned char	*src_temp;

	i = 0;
	if (!src && !dest)
		return (dest);
	dest_temp = dest;
	src_temp = (unsigned char *)src;
	while (n > 0)
	{
		dest_temp[i] = src_temp[i];
		i++;
		n--;
	}
	return (dest);
}
