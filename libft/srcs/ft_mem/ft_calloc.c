/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 21:52:54 by nkuydin           #+#    #+#             */
/*   Updated: 2025/08/29 23:49:40 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t data, size_t size)
{
	unsigned char	*temp;
	size_t			total;

	total = data * size;
	if (total == 0)
		return (malloc(0));
	else if ((long) data < 0 || (long) size < 0)
		return (0);
	temp = malloc(total);
	if (!temp)
		return (0);
	ft_bzero(temp, total);
	return (temp);
}
