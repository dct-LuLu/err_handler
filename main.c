/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 09:55:16 by jaubry--          #+#    #+#             */
/*   Updated: 2025/09/10 11:06:57 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define ERR_LOG_FILENAME ".err_log.txt"

typedef struct s_err_token
{
	unsigned char	err_lib_code;
	unsigned char	err_code;
	char			err_msg[ERR_MSG_MAX_LEN];
	void			(*)err_msg_func(char *, t_err_arg args);
}			t_err_token;

typedef sturct s_err_arg
{
	int		numerical_arg;
	void	*pointer_arg;
}

void	ass_serror(int err_lib_code, int err_code)
{

}

void	add_error(int err_code, const char *file, const int line, const char *func)
{
	static t_err_stack	err_stack[MAX_STACK];
	static size_t		err_stack_num = 0;

	err_stack[err_stack_num] = (t_err_stack){.err = err_code, .file = file, .line = line, .func = func}
}

int	error(int err_code, const char *file, const int line, const char *func)
{
	//const static	err_log_fd = open(ERR_LOG_FILENAME, O_RDWR | O_CREAT | O_TRUNC, 0644);
	static	size_t	err_stack_num = 0;

	printf("%*s[%s:%d] in %s()\n", err_stack_num * 4, "", file, line, func);
	printf("%*sError %d err_code\n\n", err_stack_num * 4, "", err_code);
	err_stack_num++;
	return (err_code);
}

int	test(void)
{
	return (error(5, __FILE__, __LINE__, __func__));
}

int	main(void)
{
	size_t	i;

	i = 0;
	while (i < 5)
	{
		if (test() != 0)
			return (error(i, __FILE__, __LINE__, __func__));
		i++;
	}
	return (0);
}
