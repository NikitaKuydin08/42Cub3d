/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 21:10:10 by nkuydin           #+#    #+#             */
/*   Updated: 2025/12/08 22:43:05 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *ptr, size_t size)
{
	char	*newptr;
	int		i;
	int		old_size;

	i = 0;
	if (ptr == NULL)
		return (malloc(size));
	old_size = ft_strlen(ptr);
	newptr = malloc(old_size + size);
	if (!newptr)
		return (NULL);
	while (i <= old_size)
	{
		newptr[i] = ptr[i];
		i++;
	}
	free(ptr);
	return (newptr);
}
