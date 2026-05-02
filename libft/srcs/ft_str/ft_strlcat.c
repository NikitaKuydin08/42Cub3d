/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:01:20 by nkuydin           #+#    #+#             */
/*   Updated: 2025/09/06 19:43:15 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	destlen;
	unsigned int	srclen;
	unsigned int	result;

	i = 0;
	destlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	if (size == 0)
		return (srclen);
	if (size <= destlen)
		return (size + srclen);
	else
		result = destlen + srclen;
	while (((i + destlen) < (size - 1)) && src[i])
	{
		dest[destlen + i] = src[i];
		i++;
	}
	dest[destlen + i] = '\0';
	return (result);
}
