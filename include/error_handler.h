/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 12:56:11 by jaubry--          #+#    #+#             */
/*   Updated: 2025/09/14 20:26:27 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLER_H
# define ERROR_HANDLER_H
# include <stdint.h>
# include <stdarg.h>
# include "libft.h"
# include <errno.h>
# include <string.h>

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
}					t_err;

t_err		get_error(const uint8_t unit_id, const uint8_t unit_errnum);
void		bulk_register_error(const size_t err_num, const uint8_t unit_id,
				const char **unit_err_msgs);

void		strf(char *output, const size_t len, const char *format, ...)
			__attribute__((format(printf, 3, 4)));
void		strfv(char *output, const size_t len, const char *format,
				va_list args);
void		add_str(char *output, const size_t max_len, char *add);

# define MAX_ERR_STACK 10
# define MAX_ERR_MSG_LEN 500

# define ERR_TEMPLATE "[%s:%d in %s()]\n%s\n\n"

char		(*stack_err_msg(void))[MAX_ERR_MSG_LEN];
void		register_complex_err_msg(const char *format, ...)
			__attribute__((format(printf, 1, 2)));
int			error(const uint16_t err_id, const char *file, const int line,
				const char *func);
void		*nul_error(const uint16_t err_id, const char *file,
				const int line, const char *func);
void		print_errs(void);

#endif//ERROR_HANDLER_H

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
