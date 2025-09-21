/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_report.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 17:35:40 by jaubry--          #+#    #+#             */
/*   Updated: 2025/09/21 17:38:14 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handler.h"

int	error(const uint16_t err_id, const char *file,
		const int line, const char *func)
{
	int	errn;

	errn = errno;
	add_stack_err_msg(err_id, file, line, func);
	if (errn)
		return (errn);
	return (-1);
}

void	*nul_error(const uint16_t err_id, const char *file,
		const int line, const char *func)
{
	error(err_id, file, line, func);
	return (NULL);
}

int	neg_error(const uint16_t err_id, const char *file,
		const int line, const char *func)
{
	error(err_id, file, line, func);
	return (-1);
}
