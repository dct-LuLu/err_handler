/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:18:46 by jaubry--          #+#    #+#             */
/*   Updated: 2025/09/21 17:29:52 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xcercall.h"

static size_t	stack_err_len(char (*errs)[MAX_ERR_MSG_LEN])
{
	size_t	len;

	len = 0;
	while (*(errs[len]))
		len++;
	return (len);
}

static void	print_err(char err[MAX_ERR_MSG_LEN], int err_stack_i)
{
	size_t	i;

	i = 0;
	while (err[i])
	{
		if ((i == 0) || (err[i - 1] == '\n'))
			printf("%*s", err_stack_i * 4, "");
		printf("%c", err[i]);
		i++;
	}
}

void	print_errs(void)
{
	char	(*errs)[MAX_ERR_MSG_LEN];
	size_t	err_stack_len;
	size_t	err_stack_i;

	errs = stack_err_msg();
	err_stack_len = stack_err_len(errs);
	err_stack_i = 0;
	while (err_stack_i < err_stack_len)
	{
		print_err(errs[err_stack_len - 1 - err_stack_i], err_stack_i);
		err_stack_i++;
	}
}
