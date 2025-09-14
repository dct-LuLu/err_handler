/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_register.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:08:21 by jaubry--          #+#    #+#             */
/*   Updated: 2025/09/14 18:13:52 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handler.h"

static t_err	(*storage_error(t_err err))[MAX_UNIT_ERR];

static void	register_error(uint8_t unit_id, uint8_t unit_errnum,
		char *err_msg)
{
	storage_error((t_err){.unit_id = unit_id, .unit_errnum = unit_errnum,
			.err_msg = err_msg});
}

static t_err	(*storage_error(t_err err))[MAX_UNIT_ERR]
{
	static t_err	errs[MAX_UNIT][MAX_UNIT_ERR];

	if ((err.unit_id != 0) && (err.unit_errnum != 0)
			&& (err.unit_id < MAX_UNIT) && (err.unit_errnum < MAX_UNIT_ERR))
		errs[err.unit_id - 1][err.unit_errnum - 1] = err;
	return (errs);
}

t_err	get_error(const uint8_t unit_id, const uint8_t unit_errnum)
{
	t_err	(*errs)[MAX_UNIT_ERR] = storage_error((t_err){.unit_id = 0, .unit_errnum = 0, .err_msg = NULL});

	if ((unit_id < MAX_UNIT) && (unit_errnum < MAX_UNIT_ERR))
		return (errs[unit_id - 1][unit_errnum - 1]);
	return (errs[0][0]);
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
