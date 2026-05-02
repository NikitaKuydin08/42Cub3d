/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:51:47 by nkuydin           #+#    #+#             */
/*   Updated: 2025/09/23 15:46:13 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int chr)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (str[i] == (char) chr)
			return ((char *) &str[i]);
		i--;
	}
	return (0);
}

// char	*ft_strrchr(const char *s, int c)
// {
// 	int		i;
// 	int		pos;

// 	i = 0;
// 	pos = -1;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == (unsigned char)c)
// 			pos = i;
// 		i++;
// 	}
// 	if (c == '\0')
// 		return ((char *)(s + i));
// 	if (pos > -1)
// 		return ((char *)(s + pos));
// 	else
// 		return (NULL);
// }
