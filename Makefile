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
# VISUL = visul

# Flags
FLAGS = -Wall -Werror -Wextra

# Paths
PATH_SRC = src/
PATH_OBJ = obj/
PATH_INC = includes/
INC_NAME = n_puzzle.hpp
# PATH_VISUL = src/visul/

# File srcs
FILES =	g_var.cpp\
		main.cpp\
		free.cpp\
		heuristic.cpp\
		algorithms.cpp\
		utils.cpp


# SRC
SRC = $(addprefix $(PATH_PARSE), $(FILES))

# include
INC = $(addprefix $(PATH_INC), $(INC_NAME))

# OBJS
OBJS = $(addprefix $(PATH_OBJ), $(FILES:.cpp=.o))


define	to_objects

echo $(OBJS)
mkdir -p $(PATH_OBJ)
g++ $(FLAGS)  -c $1 -o $2 -I $(PATH_INC)

endef

define	to_binary

g++ -g $1 -o $2 -I $(PATH_INC)

endef


all: $(NAME)

$(NAME): $(OBJS)
	$(call to_binary, $(OBJS), $(NAME))

$(OBJS)%.o: $(SRC)%.cpp $(INC)
	$(call to_objects, $<, $@)

# $(PATH_OBJ)%.o: $(PATH_CLASS)%.cpp
# 	$(call to_objects, $<, $@)

# $(VISUL): $(OBJS_VISUL)
# 	$(call to_binary, $(OBJS_VISUL), $(VISUL))

# $(PATH_OBJ)%.o: $(PATH_VISUL)%.cpp
# 	$(call to_objects, $<, $@)


clean:
	rm -rf $(PATH_OBJ)

fclean: clean
	rm -rf $(NAME) $(VISUL)

re: fclean all

.PHONY: all clean fclean re visul
