# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/31 15:41:02 by tdubois           #+#    #+#              #
#    Updated: 2023/04/13 20:45:15 by tdubois          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%% CONFIGURATION %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

MAKEFLAGS	+=	--no-print-directory

.POSIX:
.SILENT:
.DELETE_ON_ERROR:
.SECONDEXPANSION:

#==============================================================================#
#==== GOALS ===================================================================#

NAME		:=	minirt

LIBMLX42	:=	lib/mlx42/build/libmlx42.a
LIBFT		:=	lib/libft/libft.a

#==============================================================================#
#==== DIRECTORIES =============================================================#

SRC			:=	src
BUILD		:=	.build

INCLUDES	:=	$(SRC) lib/libft/include lib/mlx42/include

#==============================================================================#
#==== COMPILATION =============================================================#

CC			:=	clang									\

CFLAGS		:=	-std=c99 -Wall -Wextra -Werror			\
				-Wunreachable-code -Ofast				\

CPPFLAGS	:=	-MP -MMD $(addprefix -I,$(INCLUDES))	\

LDFLAGS		:=	-Llib/libft -lft						\
				-Llib/mlx42/build -lmlx42				\
				-ldl -lglfw -pthread -lm				\

ifdef DEBUG
CFLAGS		+=	-ggdb3 -Wno-unused-function
endif

#==============================================================================#
#==== SOURCES =================================================================#

#TODO
SRCS	:=	$(shell fd -g '*.c' -E '*.test.c' $(SRC))

#==============================================================================#
#==== BUILD FILES =============================================================#

OBJS	:=	$(SRCS:%.c=$(BUILD)/%.o)
DEPS	:=	$(SRCS:%.c=$(BUILD)/%.d)
DIRS	:=	$(sort $(shell dirname $(BUILD) $(OBJS)))

#******************************************************************************#
#**** PHONY RULES *************************************************************#

.PHONY:	all				\
		libft objs		\
		clean fclean re	\

all: | $(LIBMLX42)					#build mlx42 once (and first)
all: objs libft $(NAME)				#build other targets every time needed

libft:								#libft may be updated during development,
	$(MAKE) -C lib/libft			#hence it's made a phony target

objs:								#build objs in parallel
ifdef OBJS
	$(MAKE) -j$(nproc) $(OBJS)
endif

clean:
	#clean libft
	$(MAKE) -C lib/libft clean
	#clean minirt
	$(info $(RED)Deleting objects$(NOC))
	rm -rf $(BUILD)

fclean: clean
	#full clean libft
	$(MAKE) -C lib/libft fclean
	#clean libmlx42
	rm -rf lib/mlx42/build
	#full clean minirt
	$(info $(RED)Deleting binary$(NOC))
	rm -rf $(NAME)

re: fclean all

#******************************************************************************#
#**** BUILD RULES *************************************************************#

$(LIBMLX42):
	cmake lib/mlx42 -B lib/mlx42/build						\
		&& cmake --build lib/mlx42/build -j$(nproc) -- -s

$(NAME): $(OBJS) $(LIBFT) $(LIBMLX42)
	$(info $(BLUE)Linking C executable $@$(NOC))
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@
	$(info $(GREEN)All done$(NOC))

$(DIRS):
	mkdir -p $@

$(OBJS): $(BUILD)/%.o: %.c | $$(@D)
	$(progress-log)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%% COLORS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

NOC			:=	$(shell printf "\033[0m")
RED			:=	$(shell printf "\e[1m\e[38;5;196m")
BLUE		:=	$(shell printf "\e[1m\e[38;5;33m")
GREEN		:=	$(shell printf "\e[1m\e[38;5;76m")
PURPLE		:=	$(shell printf "\033[1;35m")

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%% PROGRESS LOG UTILS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

objs: export N		:=	0
objs: export NTOTAL	?=	$(shell make NTOTAL=1 -n $(OBJS) | grep clang | wc -l)

define progress-log =
	$(info [$(words $(N))/$(NTOTAL)] $(PURPLE)Building $< $(NOC))
	$(eval N += 1)
endef
