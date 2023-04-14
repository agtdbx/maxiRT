#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%% CONFIGURATION %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

[private]
@default:
    just --list --unsorted --list-prefix '‧‧‧‧ '

GREEN   :=  `printf '\e[92m'`
NC      :=  `printf '\e[0m'`

#==============================================================================#
#=== BUILD ====================================================================#

#run minirt
@run *argv: build
	printf -- '-%.s' $(seq $(tput cols))
	printf '\r---- running without valgrind \n'
	printf -- '-%.s' $(seq $(tput cols))
	./minirt {{argv}}

#run minirt through valgrind
@mem *argv: build
	printf -- '-%.s' $(seq $(tput cols))
	printf '\r---- running within valgrind \n'
	printf -- '-%.s' $(seq $(tput cols))
	valgrind ./minirt {{argv}}

#build project
@build:
    make DEBUG=1

#rebuild project
@re: && build
    make clean

#clean project
@clean:
    make fclean

#==============================================================================#
#==== TESTS ===================================================================#

#run all tests
@test: unit lint
    echo "{{GREEN}}TESTS OK!{{NC}}"

#**** LINT ********************************************************************#

#run static analysis (norminette)
@lint:
    fd	. -e .c -e .h					\
    	-E '*.test.c' -E 'greatest.h'	\
    	src  lib/libft					\
    	-X norminette | { ! grep Error; }

#**** UNIT ********************************************************************#

#run unit tests
@unit:
    make -f .unit.mk
    ./tests/gt-run ./unit
