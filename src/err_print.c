/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:18:46 by jaubry--          #+#    #+#             */
/*   Updated: 2025/09/14 20:19:28 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handler.h"

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
			if ((errs[i][j] == '\n') || (j == 0))
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
