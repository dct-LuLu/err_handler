/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:01:45 by jaubry--          #+#    #+#             */
/*   Updated: 2025/09/12 20:18:08 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	strf_recu_putnbr(char *output, size_t len, long int nb)
{
	int	ret;

	ret = 0;
	if ((nb > 0) && (len > 0))
	{
		ret = 1 + strf_recu_putnbr(output + 1, len - 1, nb / 10);
		*output = (nb % 10) + '0';
	}
	return (ret);
}

size_t	strf_putnbr(char *output, size_t len, long int nb)
{
	size_t	write_len;

	write_len = 0;
	if ((nb < 0) && (len > 0))
	{
		output[write_len] = '-';
		nb = -nb;
		write_len++;
		len--;
	}
	if ((nb == 0) && (len > 0))
	{
		output[write_len] = '0';
		write_len++;
		len--;
	}
	else
		write_len += strf_recu_putnbr(output, len, nb);
	return (write_len);
}

size_t	strf_putstr(char *output, const size_t len, const char *str)
{
	const size_t	str_len = ft_strlen(str);

	if (str_len > len)
	{
		ft_memcpy(output, str, len);
		return (len);
	}
	else
	{
		ft_memcpy(output, str, str_len);
		return (str_len);
	}
}

size_t	strf_handler(char *output, const size_t len, const char specifier,
		va_list args);
{
	if (specifier == 'c')
		output[0] = va_args(args, int);//char ?
	else if (specifier == 's')
		return (strf_putstr(output, len, va_args(args, char *)));
	else
		output[0] = specifier;
	return (1);
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
			write_i += strf_handler(output + write_i, len - 1 - write_i, format[++read_i], args);
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
