# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 15:54:50 by rarraji           #+#    #+#              #
#    Updated: 2023/09/18 22:47:05 by rarraji          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= CUB3D
	
CC		= cc
FLAGS	= -Wall -Wextra -Werror -fsanitize=address -g
RM		= rm -rf
SRC		= get_next_line_utils.c  mehdiCub3d.c ft_printf.c get_next_line.c
# 
IMLX	     = -I MLX42/include
MLX        = MLX42/build/libmlx42.a
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit
GLFW       = -I include -lglfw -L"/goinfre/$(USER)/homebrew/opt/glfw/lib/"
# 
#Colors:
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m

run: all
	@./CUB3D map.ber

all: $(NAME)

$(NAME): $(SRC)
	@printf "$(YELLOW) Compiling $(NAME)... \n"
	@ $(CC) $(FLAGS) $(MLX) $(FRAMEWORKS) $(GLFW) $(SRC) -o $(NAME)
	@printf "$(GREEN) Executable ready.\n"

clean:
	@$(RM) $(NAME)
	@printf "$(RED)    - Executable removed.\n"

fclean:
	@$(RM) $(NAME)
	@printf "$(RED)    - Executable removed.\n"

re: clean all run
