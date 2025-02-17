# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aleortiz <aleortiz@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/28 15:18:44 by aleortiz          #+#    #+#              #
#    Updated: 2025/02/05 16:20:00 by aleortiz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Nombre libreria compilada
NAME = libftprintf.a

#Flas para compilar la libreria
LIBCC = ar rcs

#Flags compilar los punto cc
CFLAGS = -Wall -Werror -Wextra -I$(LIBFT_D)

#Comando para remover archivos innecesarios 
RM = rm -f

#Caminos de ficheros
LIBFT_D = ./libftb
SRC_D = ./src

#Conversión de variables 
FILES = $(SRC_D)/ft_printf.c\
		$(SRC_D)/ft_print_str.c\
		$(SRC_D)/ft_print_hexa.c\
		$(SRC_D)/ft_print_decimal.c\
		$(SRC_D)/ft_print_unsigned.c\
		$(SRC_D)/ft_print_pointer.c

OBJ = $(FILES:.c=.o)

#Reglas del make
all: $(NAME)

makelibft : 
	@make -C $(LIBFT_D)
	@cp $(LIBFT_D)/libft.a .
	@mv libft.a $(NAME)

%.o : $(SRC_D)/%.c
	@cc $(CFLAGS) -c $< -o $@

$(NAME): makelibft $(OBJ)
	@$(LIBCC) $(NAME) $(OBJ)

clean:
	@$(RM) -R $(OBJ)
	@make clean -C $(LIBFT_D)

fclean: clean
	@$(RM) $(LIBFT_D)/libft.a
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re	
