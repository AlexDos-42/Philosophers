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

PHILO_ONE = philo_one
PHILO_TWO = philo_two
PHILO_THREE = philo_three

all: $(PHILO_ONE) $(PHILO_TWO) $(PHILO_THREE)

$(PHILO_ONE):
	echo "$(_YELLOW)Philo_one$(_R)"
	make -C ./philo_one MAKEFLAGS=
	cp -rf ./philo_one/philo_one ./philo_one

$(PHILO_TWO):
	echo "$(_YELLOW)Philo_two$(_R)"
	make -C ./philo_two MAKEFLAGS=
	cp -rf ./philo_two/philo_two ./philo_two

$(PHILO_THREE):
	echo "$(_YELLOW)Philo_three$(_R)"
	make -C ./philo_three MAKEFLAGS=
	cp -rf ./philo_three/philo_three ./philo_three

clean:
	@echo "$(_BLUE)Clean$(_R)"
	@make clean -C ./philo_one
	@make clean -C ./philo_two
	@make clean -C ./philo_three

fclean:	clean
	@echo "$(_BLUE)Fclean$(_R)"
	@make fclean -C ./philo_one
	@make fclean -C ./philo_two
	@make fclean -C ./philo_three
	rm $(PHILO_ONE))
	rm $(PHILO_TWO))
	rm $(PHILO_THREE))

re:	fclean all

titre:
	@echo "\e[1;93mPhilo_One - 42 project -$(_R)"
	@echo "\e[1;93m________________________$(_R)"

.PHONY:	all clean fclean re titre
