/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_stack_msg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:51:48 by jaubry--          #+#    #+#             */
/*   Updated: 2025/09/21 17:41:00 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handler.h"

char	(*stack_err_msg(void))[MAX_ERR_MSG_LEN]
{
	static char		stack_err_msg[MAX_ERR_STACK][MAX_ERR_MSG_LEN];

	return (stack_err_msg);
}

char	*get_stack_err_msg(ssize_t stack_err_i)
{
	static size_t	last_stack_err_i = 0;
	const char		*err_msg = stack_err_msg()[last_stack_err_i];

	if (stack_err_i != -1)
		last_stack_err_i++;
	return ((char *)err_msg);
}

void	add_stack_err_msg(const uint16_t err_id, const char *file,
		const int line, const char *func)
{
	static size_t	stack_err_i = 0;
	const t_err		err = fetch_error(unit_id_unpack_err(err_id),
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
		ft_strlcat(buffer, ":\n", MAX_ERR_MSG_LEN);
		ft_strlcat(buffer, strerror(errno), MAX_ERR_MSG_LEN);
		errno = 0;
	}
	strf(err_msg_ptr, MAX_ERR_MSG_LEN, ERR_TEMPLATE,
		file, line, func, buffer);
	stack_err_i++;
}
