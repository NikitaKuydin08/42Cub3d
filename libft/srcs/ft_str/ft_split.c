/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:50:45 by nkuydin           #+#    #+#             */
/*   Updated: 2025/09/03 23:39:03 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char c);
static char	**free_mem(char **res, int c);
static int	size(const char *str, char c);
static char	*fill_word(const char *str, char c);

char	**ft_split(const char *str, char c)
{
	char	**array;
	int		i;
	int		count;

	i = 0;
	count = 0;
	array = (char **)malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (!array)
		return (0);
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] && str[i] != c)
		{
			array[count] = fill_word(&str[i], c);
			if (array[count] == 0)
				return (free_mem(array, count));
			count++;
		}
		while (str[i] != c && str[i])
			i++;
	}
	array[count] = 0;
	return (array);
}

// AA|A
// |AAA
// AAA|
// A||A

static int	count_words(const char *str, char c)
{
	int	i;
	int	start_word;
	int	count;

	i = 0;
	start_word = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			start_word = 0;
		else if (start_word == 0)
		{
			start_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static int	size(const char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

static char	*fill_word(const char *str, char c)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc(sizeof(char) * (size(str, c) + 1));
	if (!word)
		return (0);
	while (str[i] && str[i] != c)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**free_mem(char **res, int c)
{
	int	i;

	i = 0;
	while (i < c)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (0);
}
