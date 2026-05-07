/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Nikita_Kuydin <nikitakuydin@qmail.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-04 04:31:48 by Nikita_Kuydin     #+#    #+#             */
/*   Updated: 2026-05-04 04:31:48 by Nikita_Kuydin    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	Need to think how to validate rgb colour, currently we 
	have it stored as a string, we need to check that:
	 - there are exatly 3 tokens, not 2 or 4
	 - there are no characters, including signs
	 - each token must to be in the range of [0, 255]

	 int	*char_to_int_rgb(int *rgb, char **array)
      --->
	 converts char* into int using ft_atoi, makes sure there are no
	 characters there.

	 int	*prepare_rgb(char *colour)
	  --->
	  basically prapares for the check

	 int  check_rgb(char *colour)
	  --->
	 checks if separate token is in the range
*/

static int	*char_to_int_rgb(int *rgb, char **array)
{
	int	i;

	i = 0;
	while ()
}

static int	*prepare_rgb(char *colour)
{
	char	**array;
	int		i;
	int		*rgb;

	i = 0;
	array = ft_split(colour, ',');
	while (array[i])
		i++;
	if (i != 3)
	{
		free_tab(array);
		return (print_err_msg(IN_NUMBER_RGB));
	}
	rgb = ft_calloc(3, sizeof(int));
	if (!rgb)
	{
		free_tab(array);
		return (print_err_msg(ERR_MALLOC));
	}
	return (char_to_int_rgb(rgb, array));
}

static int  check_rgb(char *colour)
{
	int	*rgb;

	rgb = prepare_rgb(colour);

	return (0);
}

int check_textures(t_data *data, t_texrgbinfo *texinfo)
{
	if (!texinfo->north || !texinfo->south || !texinfo->ceiling
		|| !texinfo->west || !texinfo->east || !texinfo->floor)
		return (print_err_msg(MISSED_TEX));
	if (check_file(texinfo->north, false)
		|| check_file(texinfo->south, false)
		|| check_file(texinfo->west, false)
		|| check_file(texinfo->east, false)
		|| check_rgb(texinfo->floor)
		|| check_rgb(texinfo->ceiling))
		return (1);
	
	return (0);
}
