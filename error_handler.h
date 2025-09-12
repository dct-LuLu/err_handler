/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 12:56:11 by jaubry--          #+#    #+#             */
/*   Updated: 2025/09/12 12:57:51 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#define ERR_BITPACK_SHIFT 8
#define ERR_BITPACK_MASK 0xFF

uint16_t	pack_err(const uint8_t unit_id, const unit8_t unit_errnum);
uint8_t		unit_id_unpack_err(const uint16_t error_code);
uint8_t		unit_errnum_unpack_err(const uint16_t error_code);



#define MAX_UNIT 255
#define MAX_UNIT_ERR 255


void		register_error(const uint8_t unit_id, const uint8_t unit_errnum,
				const char *err_msg);

t_err	get_error(const uint8_t unit_id, const uint8_t unit_errnum);
