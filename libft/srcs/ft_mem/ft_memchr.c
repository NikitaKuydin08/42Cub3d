/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:27:51 by nkuydin           #+#    #+#             */
/*   Updated: 2025/08/29 18:03:53 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int chr, size_t n)
{
	unsigned int	i;
	unsigned char	*string;

	i = 0;
	string = (unsigned char *) str;
	while (n > 0)
	{
		if (string[i] == (unsigned char) chr)
			return ((unsigned char *) &str[i]);
		i++;
		n--;
	}
	return (0);
}
