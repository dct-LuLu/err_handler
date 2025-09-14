/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_stack_msg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:51:48 by jaubry--          #+#    #+#             */
/*   Updated: 2025/09/14 19:49:09 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handler.h"


static char	(*stack_err_msg(void))[MAX_ERR_MSG_LEN]
{
	static char		stack_err_msg[MAX_ERR_STACK][MAX_ERR_MSG_LEN];

	return (stack_err_msg);
}

static char	*get_stack_err_msg(ssize_t stack_err_i)
{
	static size_t	last_stack_err_i = 0;
	const char		*err_msg = stack_err_msg()[last_stack_err_i];

	if (stack_err_i != -1)
		last_stack_err_i++;
	return ((char *)err_msg);
}

void	add_str(char *output, const size_t max_len, char *add);

static void	add_stack_err_msg(const uint16_t err_id, const char *file,
		const int line, const char *func)
{
	static size_t	stack_err_i = 0;
	const t_err		err = get_error(unit_id_unpack_err(err_id),
			unit_errnum_unpack_err(err_id));
	char			*err_msg_ptr;
	char			buffer[MAX_ERR_MSG_LEN];

	err_msg_ptr = get_stack_err_msg(stack_err_i);
	if (*err_msg_ptr)
		ft_memcpy(buffer, err_msg_ptr, ft_strlen(err_msg_ptr) + 1);
	else
		ft_memcpy(buffer, err.err_msg, ft_strlen(err.err_msg) + 1);
	if (errno)
	{
		add_str(buffer, MAX_ERR_MSG_LEN, ":\n");
		add_str(buffer, MAX_ERR_MSG_LEN, strerror(errno));
		errno = 0;
	}
	strf(err_msg_ptr, MAX_ERR_MSG_LEN, ERR_TEMPLATE,
			file, line, func, buffer);
	stack_err_i++;
}

int	error(const uint16_t err_id, const char *file, const int line, const char *func)
{
	int	errn;

	errn = errno;
	add_stack_err_msg(err_id, file, line, func);
	if (errn)
		return (errn);
	return (-1);
}

void	*nul_error(const uint16_t err_id, const char *file, const int line, const char *func)
{
	error(err_id, file, line, func);
	return (NULL);
}

int		neg_error(const uint16_t err_id, const char *file, const int line, const char *func)
{
	error(err_id, file, line, func);
	return (-1);
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

__attribute__((format(printf, 1, 2)))
void	register_complex_err_msg(const char *format, ...)
{
	char	*err_msg_ptr;
	char	buffer[MAX_ERR_MSG_LEN];
	va_list	args;
	int		errn;
	
	errn = errno;
	va_start(args, format);
	err_msg_ptr = get_stack_err_msg(-1);
	strfv(buffer, MAX_ERR_MSG_LEN, format, args);
	if (*err_msg_ptr)
		add_str(err_msg_ptr, MAX_ERR_MSG_LEN, "\n");
	add_str(err_msg_ptr, MAX_ERR_MSG_LEN, buffer);
	va_end(args);
	errno = errn;
}



void	print_errs(void)
{
	char	(*errs)[MAX_ERR_MSG_LEN];
	int		i;
	int		err_stack_num;

	err_stack_num = 0;
	errs = stack_err_msg();
	i = 0;
	while (*(errs[i]))
		i++;
	i--;
	int j;
	int	k;
	while (i >= 0)
	{
		j = 0;
		while (errs[i][j])
		{
			if (errs[i][j] == '\n' || j == 0)
			{
				k = 0;
				if (j != 0)
				{
					printf("\n");
					j++;
				}
				while (k < err_stack_num * 4)
				{
					printf(" ");
					k++;
				}
			}
			printf("%c", errs[i][j]);
			j++;
		}
		i--;
		err_stack_num++;
	}
}
