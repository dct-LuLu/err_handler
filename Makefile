# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/27 01:19:17 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/12 06:32:53 by jaubry--         ###   ########.fr        #
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


all:		$(NAME)
fast:		$(NAME)
debug:		$(NAME)
inspect:	$(NAME)
profile:	$(NAME)
san-mem:	$(NAME)
san-leak:	$(NAME)
san-ub:		$(NAME)

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
	@echo -e "\tall, $(NAME)\t\t: Build the library"
	@echo -e "\tdebug\t\t\t\t: Build the library with debug symbols"
	@echo -e "\tre\t\t\t\t: Rebuild $(NAME)"
	@echo
	@echo -e "\tclean\t\t\t\t: Remove object files"
	@echo -e "\tfclean\t\t\t\t: Remove object files, libraries"
	@echo
	@echo -e "\tprint-%\t\t\t\t: Prints makefile variable content when replacing '%'"

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true

clean:
	$(call rm-obj-msg)
	@rm -rf $(OBJDIR) $(DEPDIR)

fclean:
	$(call rm-obj-msg)
	@rm -rf $(OBJDIR) $(DEPDIR)
	$(call rm-lib-msg)
	@rm -f $(NAME)

re:			fclean all
refast:		fclean fast
redebug:	fclean debug
reinspect:	fclean inspect
reprofile:	fclean profile
resan-mem:	fclean san-mem
resan-leak:	fclean san-leak
resan-ub:	fclean san-ub

-include $(DEPS)

.PHONY: all clean fclean
.PHONY: help buildmsg
.PHONY: re refast redebug reinspect reprofile resan-mem resan-leak resan-ub
