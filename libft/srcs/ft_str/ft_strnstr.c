/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 18:04:53 by nkuydin           #+#    #+#             */
/*   Updated: 2025/08/29 20:51:32 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (to_find[j] == '\0')
		return ((char *) src);
	while (i < len && src[i])
	{
		j = 0;
		while (to_find[j] == src[i + j] && (i + j) < len
			&& to_find[j])
			j++;
		if (to_find[j] == '\0')
			return ((char *)(src + i));
		i++;
	}
	return (0);
}
