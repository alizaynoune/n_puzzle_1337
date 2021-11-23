# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 13:00:30 by alzaynou          #+#    #+#              #
#    Updated: 2021/11/23 18:59:49 by alzaynou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of out
NAME = n_puzzle

# Flags
FLAGS = -Wall -Werror -Wextra

# Paths
PATH_SRC = src/
PATH_OBJ = obj/
PATH_INC = includes/
PATH_PARSE = src/parse/
PATH_CLASS = src/class/

# File srcs
FILES_SRCS = main.cpp

# File parse
FILES_PARSE = parse_flags.cpp

# File Class
FILES_CLASS = class.cpp


# SRC
SRC = $(addprefix $(PATH_PARSE), $(FILES_PARSE))

# OBJS
OBJS := $(addprefix $(PATH_OBJ), $(FILES_PARSE:.cpp=.o)) \
	$(addprefix $(PATH_OBJ), $(FILES_CLASS:.cpp=.o))\
	$(addprefix $(PATH_OBJ), $(FILES_SRCS:.cpp=.o))


define	to_objects

echo $(OBJS)
mkdir -p $(PATH_OBJ)
g++ $(FLAGS) -c $1 -o $2 -I $(PATH_INC)

endef

define	to_binary

g++ $(FLAGS) $(OBJS) -o $(NAME) -I $(PATH_INC)

endef


all: $(NAME)

$(NAME): $(OBJS)
	$(call to_binary)

$(PATH_OBJ)%.o: $(PATH_SRC)%.cpp
	$(call to_objects, $<, $@)

$(PATH_OBJ)%.o: $(PATH_PARSE)%.cpp
	$(call to_objects, $<, $@)

$(PATH_OBJ)%.o: $(PATH_CLASS)%.cpp
	$(call to_objects, $<, $@)


clean:
	rm -rf $(PATH_OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re


