# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/14 08:18:04 by jaubry--          #+#    #+#              #
#    Updated: 2025/09/21 17:37:38 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

STRF_SRCS	= err_register.c \
			  err_bitpack.c \
			  err_stack_msg.c \
			  err_print.c \
			  err_report.c

SRCS		+= $(addprefix $(SRCDIR)/, $(STRF_SRCS))

vpath %.c $(SRCDIR)
