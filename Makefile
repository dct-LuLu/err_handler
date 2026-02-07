# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/27 01:19:17 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/07 02:43:53 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOTDIR		?= .
include $(ROOTDIR)/mkidir/make_utils.mk

LIBNAME		= libxcerrcal

# Directories
CDIR		= xcerrcal
SRCDIR		= src
OBJDIR		= .obj
DEPDIR		= .dep

LIBFTDIR	= $(LIBDIR)/libft

# Includes
include $(LIBFTDIR)/includes.mk includes.mk

INCLUDES	= $(INCDIRS_XCERRCAL) \
			  $(addprefix $(LIBFTDIR)/, $(INCDIRS_LIBFT))

# Output
NAME		= $(LIBNAME).a
LIBFT		= $(LIBFTDIR)/libft.a

# Compiler and flags
CC			?= cc

CFLAGS		= -Wall -Wextra -Werror \
			  -std=gnu11

DFLAGS		= -MMD -MP -MF $(DEPDIR)/$*.d

IFLAGS		= $(addprefix -I,$(INCLUDES))

CFLAGS		+= $(SANITIZE_FLAGS) $(INSPECT_FLAGS) $(PROFILE_FLAGS) $(FFLAGS)
CF			= $(CC) $(CFLAGS) $(IFLAGS)

AR          = $(if $(findstring -flto,$(FFLAGS)),$(FAST_AR),$(STD_AR))
ARFLAGS		= rcs
RANLIB      = $(if $(findstring -flto,$(FFLAGS)),$(FAST_RANLIB),$(STD_RANLIB))

# VPATH
vpath %.h $(INLUDES)
vpath %.o $(OBJDIR) $(LIBFTDIR)/$(OBJDIR)
vpath %.d $(DEPDIR) $(LIBFTDIR)/$(DEPDIR)

# Sources
MKS			= src.mk

include $(addprefix $(SRCDIR)/, $(MKS))

OBJS		= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
DEPS		= $(addprefix $(DEPDIR)/, $(notdir $(SRCS:.o=.d)))

all:	$(NAME)
fast:	$(NAME)
inspect:$(NAME)
profile:$(NAME)

$(NAME): $(OBJS) $(INCLUDES)
	$(call ar-msg)
	@$(AR) $(ARFLAGS) $@ $(OBJS)
ifeq ($(FAST),1)
	@$(RANLIB) $@
endif
	$(call ar-finish-msg)

$(OBJDIR)/%.o: %.c $(INCLUDES) | buildmsg $(OBJDIR) $(DEPDIR)
	$(call lib-compile-obj-msg)
	@$(CF) $(DFLAGS) -c $< -o $@

$(OBJDIR) $(DEPDIR):
	$(call create-dir-msg)
	@mkdir -p $@

buildmsg:
ifneq ($(shell [ -f $(NAME) ] && echo exists),exists)
	$(call lib-build-msg)
endif

help:
	@echo "Available targets:"
	@echo "  all     : Build the library"
	@echo "  clean   : Remove object files"
	@echo "  fclean  : Remove object files and library"
	@echo "  re      : Rebuild everything"

clean:
	$(call rm-obj-msg)
	@rm -rf $(OBJDIR) $(DEPDIR)

fclean:
	$(call rm-obj-msg)
	@rm -rf $(OBJDIR) $(DEPDIR)
	$(call rm-lib-msg)
	@rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re debug help buildmsg
