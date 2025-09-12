/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:01:45 by jaubry--          #+#    #+#             */
/*   Updated: 2025/09/12 13:26:02 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


size_t	strf_putstr()

size_t	strf_handler(char *output, const size_t len, const char specifier,
		va_list args);
{
	if (specifier == 'c')
	{
		output[0] = va_args(args, int);//char ?
		return (1);
	}
	else if (specifier == 's')
	{

	}
}

/*
	Function meant to do same as printf but writes on an string, with max len
	and uses `__attribute__` for compiler check arg based on format
*/
void strf(char *output, const size_t len, const char *format, ...)
	__attribute__ ((format (printf, 3, 4)));
{
	va_list	args;
	size_t	read_i;
	size_t	write_i;

	read_i = 0;
	write_i = 0;
	va_start(args, format);
	while (format[read_i] && (write_i < (len - 1)))
	{
		if (format[read_i] == '%')
			write_i += strf_handler(output + write_i, len - write_i, format[++read_i], args);
		else
		{
			output[write_i] = format[read_i];
			write_i++;
		}
		read_i++;
	}
	output[write_i] = '\0';
	va_end(args);
}
