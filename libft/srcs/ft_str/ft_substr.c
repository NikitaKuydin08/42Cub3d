/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 11:51:38 by nkuydin           #+#    #+#             */
/*   Updated: 2025/08/31 15:31:43 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	char			*tab;
	size_t			i;
	unsigned int	str_len;

	i = 0;
	str_len = ft_strlen(str);
	if (!str)
		return (0);
	if (start > str_len)
		return (ft_strdup(""));
	if (len > str_len - start)
		len = str_len - start;
	tab = ft_calloc(len + 1, sizeof(char));
	if (!tab)
		return (0);
	while (i < len)
	{
		tab[i] = str[start];
		start++;
		i++;
	}
	return (tab);
}

/*  If original string is empty, return NULL.
	If start index is bigger than the length of the orig. string,
	return empty string.
	If length of substring bigger than the length of orig. string
	after start index, we update length of the substing to match
	the left out string. Allocate memory of tab through calloc,
	rewrite characters from orig. string to the substring*/