/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xcerrcal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 12:56:11 by jaubry--          #+#    #+#             */
/*   Updated: 2025/10/09 13:51:40 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XCERRCAL_H
# define XCERRCAL_H
# include <stdint.h>
# include <stdarg.h>
# include <errno.h>
# include <string.h>
# include "libft.h"

# define FL __FILE__
# define LN __LINE__
# define FC __func__

# define ERR_BITPACK_SHIFT 8
# define ERR_BITPACK_MASK 0xFF

uint16_t	pack_err(const uint8_t unit_id, const uint8_t unit_errnum);
uint8_t		unit_id_unpack_err(const uint16_t error_code);
uint8_t		unit_errnum_unpack_err(const uint16_t error_code);

# define MAX_UNIT 255
# define MAX_UNIT_ERR 255

typedef struct s_err
{
	uint8_t	unit_id;
	uint8_t	unit_errnum;
	char	*err_msg;
}			t_err;

typedef t_err	t_errs_registry[MAX_UNIT_ERR];

t_err		fetch_error(const uint8_t unit_id, const uint8_t unit_errnum);
void		bulk_register_error(const size_t err_num, const uint8_t unit_id,
				const char **unit_err_msgs);
void		register_complex_err_msg(const char *format, ...)
			__attribute__((format(printf, 1, 2)));

# define MAX_ERR_STACK 10
# define MAX_ERR_MSG_LEN 500

# define ERR_TEMPLATE "[%s:%d] in %s()\n%s\n\n"

char		(*stack_err_msg(void))[MAX_ERR_MSG_LEN];
char		*get_stack_err_msg(ssize_t stack_err_i);
void		add_stack_err_msg(const uint16_t err_id, const char *file,
			const int line, const char *func);

int			error(const uint16_t err_id, const char *file, const int line,
				const char *func);
int			neg_error(const uint16_t err_id, const char *file, const int line,
				const char *func);
void		*nul_error(const uint16_t err_id, const char *file,
				const int line, const char *func);

void		print_errs(void);

#endif//XCERRCAL_H

/*
//naming scheme:

// units:
# define BIN //center code
# define LFT //libft
# define MLXW //mlx wrapper
# define FRDR //font renderer
# define MUI //mlx ui

// error code:
#define unit_E_errname
#define unit_E_MSG_errname


#define LFT 2
#define LFT_E_STRCPY 5
#define LFT_E_MSG_STRCPY_ "ft_strcpy failed"
*/
