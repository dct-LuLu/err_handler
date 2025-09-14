/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:01:45 by jaubry--          #+#    #+#             */
/*   Updated: 2025/09/14 20:18:18 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handler.h"

#define HEX_MAJ "0123456789ABCDEF"
#define HEX_MIN "0123456789abcdef"

static size_t	strf_recu_puthex(char *output, size_t len,
		long unsigned int nb, char *charset)
{
	size_t	write_len;

	write_len = 0;
	if ((nb > 0)  && (len > 0))
	{
		write_len = 1 + strf_recu_puthex(output, len - 1, nb / 16, charset);
		output[write_len - 1] = charset[nb % 16];
	}
	return (write_len);
}

/*
	Currently does not support negative values
*/
size_t	strf_puthex(char *output, size_t len, long unsigned int nb, bool maj)
{
	char	charset[16];
	size_t	write_len;

	if (maj)
		ft_memcpy(charset, HEX_MAJ, 16);
	else
		ft_memcpy(charset, HEX_MIN, 16);
	write_len = 0;
	if (nb == 0 && (len > 0))
	{
		output[write_len] = '0';
		write_len++;
		len--;
	}
	else
		write_len += strf_recu_puthex(output + write_len, len, nb, charset);
	return (write_len);
}



static size_t	strf_recu_putnbr(char *output, size_t len, long int nb)
{
	size_t	write_len;

	write_len = 0;
	if ((nb > 0) && (len > 0))
	{
		write_len = 1 + strf_recu_putnbr(output, len - 1, nb / 10);
		output[write_len - 1] = (nb % 10) + '0';
	}
	return (write_len);
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
		write_len += strf_recu_putnbr(output + write_len, len, nb);
	return (write_len);
}

#define STR_NULL "(null)"

size_t	strf_putstr(char *output, const size_t len, const char *str)
{
	size_t	str_len;

	if (str == NULL)
		return (strf_putstr(output, len, STR_NULL));
	str_len = ft_strlen(str);
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


#define PTR_NIL "(nil)"
#define HEX_PREFIX "0x"

size_t	strf_putptr(char *output, size_t len, long unsigned int ptr)
{
	size_t	write_len;

	write_len = 0;
	if (!ptr)
		return (strf_putstr(output, len, PTR_NIL));
	else
	{
		write_len += strf_putstr(output, len, HEX_PREFIX);
		len -= write_len;
		if (len > 0)
			write_len += strf_puthex(output + write_len, len, ptr, false);
	}
	return (write_len);
}


size_t	strf_handler(char *output, const size_t len, const char specifier,
		va_list args)
{
	if (specifier == 'c')
		output[0] = va_arg(args, int);//char ?
	else if (specifier == 's')
		return (strf_putstr(output, len, va_arg(args, char *)));
	else if (specifier == 'p')
		return (strf_putptr(output, len, va_arg(args, long unsigned)));
	else if ((specifier == 'd') || (specifier == 'i'))
		return (strf_putnbr(output, len, va_arg(args, int)));
	else if (specifier == 'u')
		return (strf_putnbr(output, len, va_arg(args, unsigned)));
	else if ((specifier == 'x') || (specifier == 'X'))
		return (strf_puthex(output, len, va_arg(args, unsigned),
					(specifier == 'X')));
	else
		output[0] = specifier;
	return (1);
}

void strfv(char *output, const size_t len, const char *format, va_list args)
{
	size_t	read_i;
	size_t	write_i;

	read_i = 0;
	write_i = 0;
	while (format[read_i] && (write_i < (len - 1)))
	{
		if (format[read_i] == '%')
			write_i += strf_handler(output + write_i,
					len - 1 - write_i, format[++read_i], args);
		else
		{
			output[write_i] = format[read_i];
			write_i++;
		}
		read_i++;
	}
	output[write_i] = '\0';
}

/*
	Function meant to do same as printf but writes on an string, with max len
	and uses `__attribute__` for compiler check arg based on format
*/
__attribute__((format(printf, 3, 4)))
void strf(char *output, const size_t len, const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	strfv(output, len, format, args);
	va_end(args);
}

void	add_str(char *output, const size_t max_len, char *add)
{
	size_t	output_len;
	size_t	i;

	i = 0;
	output_len = ft_strlen(output);
	while ((output_len + i < max_len - 1) && add[i])
	{
		output[output_len + i] = add[i];
		i++;
	}
	output[output_len + i] = '\0';
}
