# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 13:00:30 by alzaynou          #+#    #+#              #
#    Updated: 2021/11/25 13:44:43 by alzaynou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of out
NAME = n_puzzle

GPP = g++
# Flags
FLAGS = -Wall -Werror -Wextra

# Paths
PATH_SRC = src/
PATH_OBJ = obj/
PATH_INC = includes/
INC_NAME = n_puzzle.hpp

# File srcs
FILES =	g_var.cpp\
		main.cpp\
		free.cpp\
		heuristic.cpp\
		algorithms.cpp\
		utils.cpp

# include
INC = $(addprefix $(PATH_INC), $(INC_NAME))

# OBJS
OBJS = $(addprefix $(PATH_OBJ), $(FILES:.cpp=.o))


#*
#** Colors
#*

DEF = 		\x1B[1;0m
RED = 		\x1B[1;31m
PURPLE =	\x1B[1;34m
BLUE = 		\x1B[1;96m
GREEN = 	\x1B[1;32m
SILVER = 	\x1B[1;90m
YELLOW = 	\x1B[1;33m


#*
#** create objects
#*

define	to_objects
@mkdir -p $(PATH_OBJ)
@$(GPP) $(FLAGS)  -c $1 -o $2 -I $(PATH_INC)
@printf "$(SILVER)[$(PURPLE)Object file$(BLUE) $(notdir $2)$(SILVER)] $(GREEN)Created.$(DEF)\n"
endef

#*
#** create binary file
#*
define	to_binary
@$(GPP) -g $1 -o $2 -I $(PATH_INC)
@printf "$(SILVER)[$(PURPLE)Binary file$(BLUE) $(notdir $(NAME))$(SILVER)] $(GREEN)Created.$(DEF)\n"
endef

all: $(NAME)

$(NAME): $(OBJS)
	$(call to_binary, $(OBJS), $(NAME))

$(PATH_OBJ)%.o: $(PATH_SRC)%.cpp $(INC)
	$(call to_objects, $<, $@)

clean:
	@rm -rf $(PATH_OBJ)
	@printf "$(SILVER)[$(PURPLE)Objects path $(YELLOW)$(PATH_OBJ)$(SILVER)] $(RED)deleted.$(DEF)\n"

fclean: clean
	@rm -rf $(NAME) $(VISUL)
	@printf "$(SILVER)[$(PURPLE)File binary $(YELLOW)$(NAME)$(SILVER)] $(RED)deleted.$(DEF)\n"

re: fclean all

.PHONY: all clean fclean re
