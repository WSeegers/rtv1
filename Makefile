# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/28 22:24:10 by wseegers          #+#    #+#              #
#    Updated: 2018/08/06 18:07:39 by wseegers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1
CC = clang
#CFLAGS = -Werror -Wall -Wextra
CFLAGS =
SDL2 = `sdl2-config --cflags --libs`
INC = -I libwtcc/include -I libmatrix -I include
LIB = -L ./libwtcc -lwtcc

SRC_PATH = src
ALL_SRC = $(wildcard src/*.c)
SRC = $(ALL_SRC:src/%=%)
BIN_PATH = bin
BIN := $(SRC:%.c=$(BIN_PATH)/%.o)
DEP := $(BIN:%.o=%.d)

OS := $(shell uname)
ifeq ($(OS), Darwin)
	SDL2 = -L ~/lib -lSDL2
else
	SDL2 = `sdl2-config --cflags --libs`
	LIB += -lm
endif

all : make_LIB $(NAME)
	@echo "wseegers" > author

make_LIB :
	./SDL_install.sh
	make -C libwtcc -j4

$(NAME) : $(BIN)
	$(CC) $(CFLAGS) $(INC) -o $@ $^ $(LIB) $(SDL2) libmatrix/*.c

$(BIN_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(BIN_PATH)
	$(CC) $(CFLAGS) $(INC) -MMD -c $< -o $@

-include $(DEP)

clean :
	rm -rf $(BIN_PATH)

fclean : clean
	rm -f $(NAME)
	rm -rf SDL2-2.0.8
	rm -rf include/SDL2
	make fclean -C libwtcc

re : fclean all

run : all
	@./$(NAME)

.PHONEY : usage all make_all  clean  fclean  re