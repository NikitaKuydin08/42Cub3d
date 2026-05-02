/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:45:14 by nkuydin           #+#    #+#             */
/*   Updated: 2025/08/28 18:19:52 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *src, int c, unsigned int n)
{
	unsigned char	*temp;
	unsigned int	i;

	i = 0;
	temp = src;
	while (n > 0)
	{
		temp[i] = (unsigned char)c;
		n--;
		i++;
	}
	return (src);
}
