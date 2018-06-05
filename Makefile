# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hvashchu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/09 18:56:15 by hvashchu          #+#    #+#              #
#    Updated: 2017/10/09 18:56:17 by hvashchu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
SRC	= 	main.c \
		draw.c \
		init.c \
		keyhook.c \
		move.c \
		parser.c \
		raycast.c

OBJ = $(SRC:.c=.o)
FLAGS = -framework OpenGL -framework AppKit -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	make -C minilibx/
	gcc -o $(NAME) $(OBJ) libft/*.o minilibx/*.o $(FLAGS)
	@echo wolf3d has been made

%.o: %.c
	gcc -c -o  $@ $<

cleanlib:
	make clean -C ./libft
	make clean -C ./minilibx

fcleanlib:
	make fclean -C ./libft
	make clean -C ./minilibx

clean: cleanlib
	rm -f $(OBJ)
	@echo *.o have been cleaned.

fclean: clean fcleanlib
	rm -f $(NAME)
	@echo *.a and *.o have been cleaned.

re: fclean all
