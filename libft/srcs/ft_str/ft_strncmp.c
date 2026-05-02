/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:00:29 by nkuydin           #+#    #+#             */
/*   Updated: 2025/08/29 13:58:10 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	char	s1[] = "Hell  ";
// 	char	s2[] = "Hello";
// 	char	a;
// 	char	a2;

// 	a = ft_strncmp(s1, s2, 5);
// 	printf("%d\n", a);
// 	a2 = strncmp(s1, s2, 5);
// 	printf("%d\n", a2);
// 	return (0);
// }
