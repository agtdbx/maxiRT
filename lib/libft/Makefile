# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 20:11:42 by tdubois           #+#    #+#              #
#    Updated: 2023/07/24 12:24:15 by tdubois          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%% CONFIGURATION %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

MAKEFLAGS	+=	--no-print-directory

.POSIX:
.SILENT:
.DELETE_ON_ERROR:
.SECONDEXPANSION:

#==============================================================================#
#==== GOALS ===================================================================#

NAME		:=	libft.a

#==============================================================================#
#==== DIRECTORIES =============================================================#

SRC			:=	src
BUILD		:=	.build
INCLUDE		:=	include

#==============================================================================#
#==== COMPILATION =============================================================#

CC			:=	clang
CFLAGS		:=	-Wall -Wextra -Werror -O3
CPPFLAGS	:=	-MP -MMD $(addprefix -I,$(INCLUDE))

ifdef DEBUG
CFLAGS		+=	-ggdb3
endif

#==============================================================================#
#==== SOURCES =================================================================#

SRCS		:=	src/ft_strlen.c \
				src/ft_strncmp.c \
				src/ft_strsep.c \
				src/ft_memcpy.c \
				src/ft_max.c \
				src/ft_strtok.c \
				src/ft_bzero.c \
				src/ft_puterr.c \
				src/ft_strdup.c \
				src/ft_substr.c \
				src/ft_strtof.c \
				src/ft_strspn.c \
				src/ft_gnl.c \
				src/ft_abs.c \
				src/ft_putstr.c \
				src/ft_min.c \
				src/ft_strcspn.c \
				src/ft_strendswith.c \
				src/ft_strrev.c \
				src/ft_basename.c \
				src/ft_strcmp.c \
				src/ft_swap.c \
				src/ft_strchr.c \
				src/ft_memdup.c \
				src/ft_memdel.c \
				src/ft_isdigit.c \
				src/ft_strlcpy.c \
				src/ft_memset.c \
				src/ft_sftoa.c \
				src/ft_strtoi.c \
				src/ft_gnl_init_buffer.c \
				src/ft_strtok_r.c \
				src/ft_putstr_fd.c \
				src/ft_gnl_r.c \
				src/ft_sitoa.c

#==============================================================================#
#==== BUILD FILES =============================================================#

OBJS		:=	$(SRCS:%.c=$(BUILD)/%.o)
DEPS		:=	$(SRCS:%.c=$(BUILD)/%.d)
DIRS		:=	$(sort $(shell dirname $(BUILD) $(OBJS)))

#******************************************************************************#
#**** PHONY RULES *************************************************************#

.PHONY:	all				\
		objs			\
		clean fclean re

all: objs $(NAME)

objs:
ifdef OBJS
	$(MAKE) -j$(nproc) $(OBJS)
endif

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -f $(NAME)

re: fclean all

#******************************************************************************#
#**** BUILD RULES *************************************************************#

$(NAME): $(OBJS) | $$(@D)
	$(info $(BLUE)Linking C static library $@$(NOC))
	ar rcs $@ $(OBJS)
	$(info $(GREEN)All done$(NOC))

$(DIRS):
	mkdir -p $@

$(OBJS): $(BUILD)/%.o: %.c | $$(@D)
	$(progress-log)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%% COLORS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

NOC			:=	$(shell printf '\033[0m')
RED			:=	$(shell printf '\033[1m\033[38;5;196m')
BLUE		:=	$(shell printf '\033[1m\033[38;5;33m')
GREEN		:=	$(shell printf '\033[1m\033[38;5;76m')
PURPLE		:=	$(shell printf '\033[1;35m')

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%% PROGRESS LOG UTILS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

objs: export N		:=	0
objs: export NTOTAL	?=	$(shell make NTOTAL=1 -n $(OBJS) | grep clang | wc -l)

define progress-log =
	$(info [$(words $(N))/$(NTOTAL)] $(PURPLE)Building $< $(NOC))
	$(eval N += 1)
endef
