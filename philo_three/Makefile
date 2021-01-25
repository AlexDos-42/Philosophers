_BOLD		=\e[1m
_R			=\e[0m

_RED		=\e[91m
_GREEN		=\e[92m
_YELLOW		=\e[93m
_BLUE		=\e[94m
_MAGENTA	=\e[35m
_CYAN		=\e[96m
_WHITE		=\e[97m

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alesanto <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/09 17:02:25 by alesanto          #+#    #+#              #
#    Updated: 2020/04/10 16:03:47 by alesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_three

SRC =	main.c \
		outils.c \
		exit.c \
		process.c \
		routine.c \
		aff.c \

### Librairies ###
HEADERS = ./includes/
INC = philo.h
vpath %.h $(HEADERS)

### Sources ###
PATHSRCS = ./srcs
SRCS = $(addprefix $(PATHSRCS)/,$(SRC))

### Objets ###
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
vpath %.c $(PATHSRCS)

### Flags ###
FLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

all: $(NAME)

$(OBJ_DIR)/%.o: $(PATHSRCS)/%.c
	@mkdir -p $(OBJ_DIR)
	@gcc $(FLAGS) -I $(HEADERS) -c $< -o $@ 
	@printf "$(_YELLOW)Compiling :$(_WHITE) $<$(_R)\n"

$(NAME): titre $(OBJ)
	@printf "$(_YELLOW)Compilation completed.$(_R)\n"
	@(gcc $(FLAGS) -I $(HEADERS) $(OBJ) -o $(NAME) -lpthread)
	@(printf "$(_YELLOW)Executable $(NAME) created.$(_R)\n")

clean:
	@printf "$(_BLUE)Clean$(_R)\n"
	@(rm -rf ./srcs/*.o)
	@(rm -rf $(OBJ_DIR))

fclean:	clean
	@printf "$(_BLUE)Fclean$(_R)\n"
	@(rm -rf $(NAME))

re:	fclean all

titre:
	@printf "\e[1;93mPhilo_Three - 42 project -$(_R)\n"
	@printf "\e[1;93m__________________________$(_R)\n"

.PHONY:	all clean fclean re titre
