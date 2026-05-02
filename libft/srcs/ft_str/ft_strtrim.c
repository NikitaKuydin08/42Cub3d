/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:00:16 by nkuydin           #+#    #+#             */
/*   Updated: 2025/09/26 19:18:24 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_to_del(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	count(const char *str, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && char_to_del(set, str[i]) == 1)
	{
		i++;
		j++;
	}
	return (j);
}

char	*ft_strtrim(const char *str, char const *set)
{
	size_t		len1;
	size_t		str_len;
	char		*buffer;

	len1 = count(str, set);
	str_len = ft_strlen(str);
	while (str_len > len1 && char_to_del(set, str[str_len - 1]) == 1)
		str_len--;
	buffer = (char *)malloc(sizeof(char) * (str_len - len1 + 1));
	if (!buffer)
		return (0);
	ft_memcpy(buffer, &str[len1], str_len - len1);
	buffer[str_len - len1] = '\0';
	return (buffer);
}
