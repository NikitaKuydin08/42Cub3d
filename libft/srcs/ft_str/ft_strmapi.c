/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:47:41 by nkuydin           #+#    #+#             */
/*   Updated: 2025/09/01 23:32:42 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *str, char (*f)(unsigned int, char))
{
	char	*buffer;
	int		i;
	int		length_str;

	i = 0;
	length_str = ft_strlen(str);
	buffer = (char *)malloc(sizeof(char) * (length_str + 1));
	if (!buffer)
		return (0);
	while (i < length_str)
	{
		buffer[i] = (*f)(i, str[i]);
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}
