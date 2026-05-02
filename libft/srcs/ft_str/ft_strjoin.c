/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 15:36:29 by nkuydin           #+#    #+#             */
/*   Updated: 2025/09/26 14:47:38 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	int		s1_len;
	int		s2_len;
	char	*tab;

	i = 0;
	j = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	tab = ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (!tab)
		return (0);
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		tab[i + j] = s2[j];
		j++;
	}
	tab[i + j] = '\0';
	return (tab);
}
