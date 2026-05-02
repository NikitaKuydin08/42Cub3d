/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 05:00:51 by nkuydin           #+#    #+#             */
/*   Updated: 2025/10/22 13:48:37 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// d or i	Signed decimal integer	392
// u	    Unsigned decimal integer	7235
// x		Unsigned hexadecimal integer	7fa
// X		Unsigned hexadecimal integer (uppercase)	7FA
// c		Character	a
// s		String of characters	sample
// p		Pointer address	b8000000	
// %		A % followed by another % character will write a single %.

// c = va_arg(args, int)
// s = va_arg(args, char *)
// d = va_arg(args, int)
// i = va_arg(args, int)
// u = va_arg(args, unsigned int)
// p = va_arg(args, unsigned long)# or 
//     #(unsigned long)va_arg(args, void *);
// x = va_arg(args, unsigned int)
// X = va_arg(args, unsigned int)

void	ft_convert(va_list args, const char *c, int *length,
			unsigned long long ptr);

int	ft_printf(const char *src, ...)
{
	va_list				args;
	int					length;
	int					i;
	unsigned long long	ptr;

	length = 0;
	i = 0;
	va_start(args, src);
	while (src[i])
	{
		ptr = 0;
		if (src[i] == '%')
			ft_convert(args, &src[++i], &length, ptr);
		else
			length += write(1, &src[i], 1);
		i++;
	}
	va_end(args);
	return (length);
}

void	ft_convert(va_list args, const char *c, int *length,
			unsigned long long ptr)
{
	if (*c == 'c')
	{
		ptr = va_arg(args, int);
		(*length) += write(1, &ptr, 1);
	}
	else if (*c == 's')
		(*length) += ft_printstr(va_arg(args, char *));
	else if (*c == 'd' || *c == 'i')
		(*length) += ft_printint(va_arg(args, int));
	else if (*c == 'x' || *c == 'X')
		(*length) += ft_printhex(va_arg(args, unsigned int), *c);
	else if (*c == 'p')
		(*length) += ft_printptr(va_arg(args, unsigned long long));
	else if (*c == 'u')
		(*length) += ft_print_unsigned(va_arg(args, unsigned int));
	else if (*c == '%')
		(*length) += write(1, "%%", 1);
}
