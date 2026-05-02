/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:39:46 by nkuydin           #+#    #+#             */
/*   Updated: 2025/08/29 17:29:35 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int chr)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char) chr)
			return ((char *) &str[i]);
		i++;
	}
	if (str[i] == (char) chr)
		return ((char *) &str[i]);
	return (0);
}
