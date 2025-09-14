# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/14 08:20:48 by jaubry--          #+#    #+#              #
#    Updated: 2025/09/14 08:21:31 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
TEST_DIR	= $(SRCDIR)/test

# Source files
TEST_SRCS	= main.c

TEST_SRCS	:= $(addprefix $(TEST_DIR)/, $(TEST_SRCS))

# VPATH
vpath %.c $(TEST_DIR)
