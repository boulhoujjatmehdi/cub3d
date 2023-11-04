# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 15:54:50 by rarraji           #+#    #+#              #
#    Updated: 2023/11/04 14:49:51 by eboulhou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= CUB3D
	
CC		= cc
FSAN  	= -g -fsanitize=address
FLAGS	= -Wall -Wextra -Werror $(FSAN)
RM		= rm -rf
P1		= mehdiCub3d.c
RAY	= $(addprefix ray_tex/, $(P1))
P2		= parse.c
PAR     = $(addprefix parse/, $(P2))




SRC		= 	$(RAY) $(PAR)\
			get_next_line.c get_next_line_utils.c

# 
IMLX		= -I MLX42/include
MLX			= MLX42/build/libmlx42.a
LIBFT		= libft/libft.a
FRAMEWORKS	= -framework Cocoa -framework OpenGL -framework IOKit
GLFW       	= -Iinclude -lglfw -L"/goinfre/$(USER)/homebrew/opt/glfw/lib/"
OBJ			= $(SRC:.c=.o)
# 
#Colors:
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m



%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@


all: $(NAME)

run: all
	@./CUB3D map.ber

$(NAME): $(OBJ) $(LIBFT) 
	@printf "$(YELLOW) Compiling $(NAME)... \n"
	$(CC)  $(FSAN) $(OBJ) $(LIBFT) $(MLX) $(GLFW)  -o $(NAME)  
	@printf "$(GREEN) Executable ready.\n"

%.o : %.c
	$(CC)  $(FSAN) -c $< -o $@ 

$(LIBFT):
	make -C libft

clean:
	$(MAKE) fclean -C libft
	$(RM) $(OBJ)
	@printf "$(RED)    - Executable removed.\n"

fclean: clean
	$(RM) $(NAME)
	@printf "$(RED)    - Executable removed.\n"

re: fclean all

