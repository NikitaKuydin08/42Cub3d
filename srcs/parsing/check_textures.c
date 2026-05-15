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
	check rgb works, now, it would be beneficial for us to convert the rgb
	to hexadecimal right away, and use it then through hexadecimal representation
	But how???

	Full recreation. 3 functions in total at the end.
	Convertion of rgb char to the decimal base 10, checking if the number is
	in the range. Making sure that there are no non-digits characters. 
	
	+1 function, to skip trailing whitespace characters between rgb values
	(before and after), but not inside of the separate values. 

	ft_split splits the string by some char into values, those values are
	null-terminated by the ft_split. 

	array[0] = "   	220   ";
	array[1] = "0";
	array[2] = "   		150";

	WE HANDLE leading whitespaces in rgb colours, we handle whitespaces
	everywhere

	Actually is_rgb_value_valis does help situation after the split 

	A lot of logic needs to be changed for the handling whitespaces in rgb
	FUCK, FUCK, FUCK

	Write a separate function for the rgb extraction from the file, because
	the texture function exited the program to fast
*/

static int	is_rgb_value_valid(char *value)
{
	int		i;
	bool	digit;

	i = 0;
	digit = false;
	while (value[i] && value[i] <= 32)
		i++;
	while (ft_isdigit(value[i]))
	{
		digit = true;
		i++;
	}
	while (value[i] && value[i] <= 32)
		i++;
	return (digit && value[i] == '\0');
}

static int	convert_n_check(char **array, uint32_t *rgb)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (!is_rgb_value_valid(array[i]))
			return (print_err_msg(CONTAINS_OTHER_CHAR));
		rgb[i] = ft_atoi(array[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (print_err_msg(OUT_OF_RANGE));
		i++;
	}
	return (0);
}

static int	check_rgb_to_hex(char *char_colour, uint32_t *hex_colour)
{
	char		**array;
	int			i;
	uint32_t	rgb[3];

	i = 0;
	array = ft_split(char_colour, ',');
	if (!array)
		return (print_err_msg(ERR_MALLOC));
	while (array[i])
		i++;
	if (i != 3)
	{
		free_tab(array);
		return (print_err_msg(INVALID_COUNT_RGB));
	}
	i = 0;
	if (convert_n_check(array, rgb))
	{
		free_tab(array);
		return (1);
	}
	free_tab(array);
	*hex_colour = (rgb[0] << 24) | (rgb[1] << 16) | (rgb[1] << 16) | (0xFF);
	return (0);
}

int	check_textures(t_texrgbinfo *texinfo)
{
	if (!texinfo->north || !texinfo->south || !texinfo->ceiling
		|| !texinfo->west || !texinfo->east || !texinfo->floor)
		return (print_err_msg(MISSED_TEX));
	if (check_file(texinfo->north, false)
		|| check_file(texinfo->south, false)
		|| check_file(texinfo->west, false)
		|| check_file(texinfo->east, false))
		return (1);
	if (check_rgb_to_hex(texinfo->floor, &texinfo->hex_floor))
		return (1);
	if (check_rgb_to_hex(texinfo->ceiling, &texinfo->hex_ceiling))
		return (1);
	return (0);
}
