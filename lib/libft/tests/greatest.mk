# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    greatest.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdubois <tdubois@student.42angouleme.fr>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 20:11:42 by tdubois           #+#    #+#              #
#    Updated: 2023/04/07 13:28:59 by tdubois          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#> should be executed at root of library folder

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%% CONFIGURATION %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

MAKEFLAGS	+=	--no-print-directory

.POSIX:
.SILENT:
.DELETE_ON_ERROR:
.SECONDEXPANSION:

#==============================================================================#
#==== GOALS ===================================================================#

NAME		:=	test

#==============================================================================#
#==== DIRECTORIES =============================================================#

SRC			:=	src
BUILD		:=	.build-greatest
INCLUDE		:=	include tests

#==============================================================================#
#==== COMPILATION =============================================================#

CC			:=	clang
CFLAGS		:=	-Wall -Wextra -Werror -ggdb3
CPPFLAGS	:=	-MP -MMD $(addprefix -I,$(INCLUDE))

#==============================================================================#
#==== SOURCES =================================================================#

SRCS		:=	$(sort $(shell fd -g '*.c' $(SRC)))

TESTS		:=	$(shell fd -g '*.test.c' $(SRC))

#==============================================================================#
#==== BUILD FILES =============================================================#

MAIN		:=	$(BUILD)/main.gen.c
MAINOBJ		:=	$(BUILD)/main.gen.o

OBJS		:=	$(SRCS:%.c=$(BUILD)/%.o)
DEPS		:=	$(SRCS:%.c=$(BUILD)/%.d)
DIRS		:=	$(sort $(shell dirname $(OBJS)))

#******************************************************************************#
#**** PHONY RULES *************************************************************#

.PHONY:	all				\
		objs			\
		clean fclean re

all: objs $(NAME)

objs:
ifdef OBJS
	$(MAKE) -f tests/greatest.mk -j$(nproc) $(OBJS)
endif

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -f $(NAME)

re: fclean all

#******************************************************************************#
#**** BUILD RULES *************************************************************#

$(NAME): $(MAINOBJ) $(OBJS) | $$(@D)
	$(info $(BLUE)Linking C static library $@$(NOC))
	$(CC) $(CFLAGS) $(MAINOBJ) $(OBJS) -o $@
	$(info $(GREEN)All done$(NOC))

$(DIRS):
	mkdir -p $@

$(OBJS): $(BUILD)/%.o: %.c | $$(@D)
	$(progress-log)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(MAIN): $(TESTS) | $$(@D)
	$(info $(PURPLE)Building $@ $(NOC))
	./tests/greatest-gen $(TESTS) > $@

$(MAINOBJ): $(MAIN) | $$(@D)
	$(info $(PURPLE)Building $@ $(NOC))
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
objs: export NTOTAL	?=	\
	$(shell make -f tests/greatest.mk NTOTAL=1 -n $(OBJS) | grep clang | wc -l)

define progress-log =
	$(info [$(words $(N))/$(NTOTAL)] $(PURPLE)Building $< $(NOC))
	$(eval N += 1)
endef
