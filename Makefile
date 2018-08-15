# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/28 22:24:10 by wseegers          #+#    #+#              #
#    Updated: 2018/08/15 15:55:29 by wseegers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1
CC = clang
CFLAGS = -Werror -Wall -Wextra
SDL2 = `sdl2-config --cflags --libs`
INC = -I libwtcc/include -I libmatrix/include -I include
LIB = -L ./libwtcc -lwtcc -L ./libmatrix -lmatrix
LIBS = libmatrix/libmatrix.a libwtcc/libwtcc.a

SRC_PATH = src
ALL_SRC = camera.c colour.c cone.c cylinder.c eval_light.c\
		  gen_scene1.c gen_scene2.c gen_scene3.c gen_scene4.c\
		  generate_screen.c light.c plane.c putpixel.c ray.c\
		  rtv1.c sphere.c vlight_set.c vshape_set.c parse_scene.c\
		  scene.c
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

all : install_sdl $(NAME)
	@echo "wseegers" > author
	
$(NAME) : $(LIBS) $(BIN)
	$(CC) $(CFLAGS) $(INC) -o $@ $^ $(LIB) $(SDL2) 

install_sdl :
	./SDL_install.sh

libmatrix/libmatrix.a : 
	make -C libmatrix -j4

libwtcc/libwtcc.a :
	make -C libwtcc -j4

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
	make fclean -C libmatrix

re : fclean all

run : all
	@./$(NAME)

debug :
	@echo $(BIN)
	@echo $(SRC)

.PHONEY : usage all make_all clean fclean re install_sdl