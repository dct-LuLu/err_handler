/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bitpacking.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 12:54:27 by jaubry--          #+#    #+#             */
/*   Updated: 2025/09/12 18:38:27 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handler.h"

uint16_t	pack_err(const uint8_t unit_id, const unit8_t unit_errnum)
{
	return ((unit_id << ERR_BITPACK_SHIFT) | unit_errnum);
}

uint8_t	unit_id_unpack_err(const uint16_t error_code)
{
	return ((error_code >> ERR_BITPACK_SHIFT) | ERR_BITPACK_MASK);
}

uint8_t	unit_errnum_unpack_err(const uint16_t error_code)
{
	return (error_code & ERR_BITPACK_MASK);
}
