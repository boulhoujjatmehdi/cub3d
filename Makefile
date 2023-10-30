# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 15:54:50 by rarraji           #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2023/10/30 12:26:22 by eboulhou         ###   ########.fr        #
=======
#    Updated: 2023/10/25 15:51:02 by eboulhou         ###   ########.fr        #
>>>>>>> 6b4267c80c8df90569f31d36df8eb47b33624538
#                                                                              #
# **************************************************************************** #

NAME	= CUB3D
	
CC		= cc
FSAN   = -fsanitize=address -g
FLAGS	= -Wall -Wextra -Werror $(FSAN)
RM		= rm -rf
SRC		= 	get_next_line_utils.c \
			mehdiCub3d.c\
			ft_printf.c\
			get_next_line.c\
			parse.c

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

run: all
	@./CUB3D map.ber

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) 
	@printf "$(YELLOW) Compiling $(NAME)... \n"
	$(CC)  $(FSAN) $(OBJ) $(LIBFT) $(MLX) $(GLFW)  -o $(NAME)  
	@printf "$(GREEN) Executable ready.\n"

<<<<<<< HEAD
%.o : %.c
	$(CC)  $(FSAN) -c $< -o $@ 
=======
>>>>>>> 6b4267c80c8df90569f31d36df8eb47b33624538

$(LIBFT):
	make -C libft

clean:
	$(MAKE) fclean -C libft
	$(RM) $(OBJ)
	@printf "$(RED)    - Executable removed.\n"

fclean: clean
	$(RM) $(NAME)
	@printf "$(RED)    - Executable removed.\n"

re: fclean run