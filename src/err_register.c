/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_register.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:08:21 by jaubry--          #+#    #+#             */
/*   Updated: 2025/09/21 17:36:34 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xcerrcal.h"

static t_errs_registry	*storage_error(t_err err)
{
	static t_err	errs[MAX_UNIT][MAX_UNIT_ERR];

	if ((err.unit_id != 0) && (err.unit_errnum != 0)
		&& (err.unit_id < MAX_UNIT) && (err.unit_errnum < MAX_UNIT_ERR))
		errs[err.unit_id - 1][err.unit_errnum - 1] = err;
	return (errs);
}

t_err	fetch_error(const uint8_t unit_id, const uint8_t unit_errnum)
{
	const t_errs_registry	*errs = storage_error((t_err)
		{.unit_id = 0, .unit_errnum = 0, .err_msg = NULL});

	if ((unit_id < MAX_UNIT) && (unit_errnum < MAX_UNIT_ERR))
		return (errs[unit_id - 1][unit_errnum - 1]);
	return (errs[0][0]);
}

static void	register_error(uint8_t unit_id, uint8_t unit_errnum,
		char *err_msg)
{
	storage_error((t_err){.unit_id = unit_id, .unit_errnum = unit_errnum,
		.err_msg = err_msg});
}

void	bulk_register_error(const size_t err_num, const uint8_t unit_id,
			const char **unit_err_msgs)
{
	size_t	i;

	i = 0;
	while (i < err_num)
	{
		register_error(unit_id, i + 1, (char *)unit_err_msgs[i]);
		i++;
	}
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
		ft_strlcat(err_msg_ptr, "\n", MAX_ERR_MSG_LEN);
	ft_strlcat(err_msg_ptr, buffer, MAX_ERR_MSG_LEN);
	va_end(args);
	errno = errn;
}
