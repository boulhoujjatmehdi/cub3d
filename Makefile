# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eboulhou <eboulhou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 15:54:50 by rarraji           #+#    #+#              #
#    Updated: 2023/11/08 08:50:03 by eboulhou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
	
CC		= cc
FLAGS	= -Wall -Wextra -Werror 
RM		= rm -rf
P1		= ray_main.c  data.c movements.c checks.c projection.c projection2.c projection3.c
RAY	= $(addprefix ray_tex/, $(P1))
P2		= parse_main.c parse1.c parse2.c parse3.c parse4.c parse5.c parse6.c parse7.c get_next_line.c get_next_line_utils.c
PAR     = $(addprefix parse/, $(P2))
SRC		= 	$(RAY) $(PAR)


IMLX		= -I MLX42/include
MLX			= MLX42/build/libmlx42.a
LIBFT		= libft/libft.a
FRAMEWORKS	= -framework Cocoa -framework OpenGL -framework IOKit
GLFW       	= -Iinclude -lglfw -L"/goinfre/$(USER)/homebrew/opt/glfw/lib/"
OBJ			= $(SRC:.c=.o)


%.o : %.c
	${CC}  ${FLAGS} -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) 
	@$(CC)  $(FLAGS) $(OBJ) $(LIBFT) $(MLX) $(GLFW)  -o $(NAME)

$(LIBFT):
	make -C libft

clean:
	make clean -C libft
	$(RM) $(OBJ)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)


re: fclean all

