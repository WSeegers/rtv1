# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/28 22:24:10 by wseegers          #+#    #+#              #
#    Updated: 2018/07/29 18:22:19 by wseegers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1
CC = clang
#CFLAGS = -Werror -Wall -Wextra
CFLAGS =
SDL2 = `sdl2-config --cflags --libs`
INC = -I libwtcc/include -I libmatrix
LIB = -L ./ -lwtcc -lm

SRC_PATH = src
ALL_SRC = $(wildcard src/*.c)
SRC = $(ALL_SRC:src/%=%)
BIN_PATH = bin
BIN := $(SRC:%.c=$(BIN_PATH)/%.o)
DEP := $(BIN:%.o=%.d)

all : make_LIB $(NAME)
	@echo "wseegers" > author

make_LIB :
	make -C libwtcc

$(NAME) : $(BIN)
	$(CC) $(CFLAGS) $(INC) -o $@ $^ $(LIB) $(SDL2) libmatrix/vec3.c

$(BIN_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(BIN_PATH)
	$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@

-include $(DEP)

clean :
	rm -rf $(BIN_PATH)

fclean : clean
	rm -f $(NAME)
	make fclean -C toolkit-wtc

re : fclean all

run : all
	@./$(NAME)

.PHONEY : usage all make_all  clean  fclean  re