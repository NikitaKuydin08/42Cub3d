/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 23:49:30 by nkuydin           #+#    #+#             */
/*   Updated: 2025/09/03 13:57:26 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *str, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	unsigned int	str_length;

	i = 0;
	str_length = ft_strlen(str);
	while (i < str_length)
	{
		(*f)(i, &str[i]);
		i++;
	}
}
