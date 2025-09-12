/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_registery.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:08:21 by jaubry--          #+#    #+#             */
/*   Updated: 2025/09/12 12:59:03 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



static t_err	**storage_error(t_err err);

typedef struct args_s	args_t;

#include <stdint.h>

typedef struct s_err
{
	const uint8_t	unit_id;
	const unit8_t	unit_errnum;
	const char		*err_msg;
	//err_msgf func
}					t_err;

void	register_error(const uint8_t unit_id, const uint8_t unit_errnum,
		const char *err_msg)
{
	storage_error((t_err){.unit_id = unit_id, .unit_errnum = unit_errnum,
			.err_msg = err_msg});
}

static t_err	**storage_error(t_err err)
{
	static t_err	errs[MAX_UNIT][MAX_UNIT_ERR];

	if ((err.unit_id != 0) && (err.unit_errnum != 0))
		errs[err.unit_id][err.unit_errnum] = err;
	return (errs);
}

t_err	get_error(const uint8_t unit_id, const uint8_t unit_errnum)
{
	const t_err	**errs = storage_error((t_err){.unit_id = 0, .unit_errnum = 0, .err_msg = NULL});

	return (errs[unit_id][unit_errnum]);
}



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

//register_error(LFT, LFT_E_STRCPY, LFT_E_MSG_STRCPY);

//error(pack_err(LFT, LFT_E_STRCPY), __FILE__, __LINE__, __FUNC__);



/*
	Could we do something like:

	Function meant to do same as printf but writes on an string, with max len
	and uses `__attribute__` for compiler check arg based on format

	void strf(char *output, size_t len, const char *format, ...)
		__attribute__ ((format (printf, 3, 4)));
	{
		
	}
*/
