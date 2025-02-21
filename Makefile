# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aleortiz <aleortiz@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/17 13:05:22 by aleortiz          #+#    #+#              #
#    Updated: 2025/02/19 19:30:10 by aleortiz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables de color  #
RESET = \033[0m
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
#=====================#

# Caminos a cabeceras y archivos fuente #
PRINT = ./utils
PRINTHEAD = ./utils/src
LIBHEADER = ./utils/libftb
SOURCEPATH= ./src
RMDIR = ./obj
#=======================================#

# Archivos fuente y crear objetos   ====================#
FILES = ./src/ft_mainpipex.c\
		./src/ft_utilspipex.c\
		./src/ft_pipexsplit.c
MYPROG = pipex.c
OBJ = $(addprefix $(RMDIR)/, $(notdir $(FILES:.c=.o)))
#=======================================================#

# Crear el .a pipex y adjuntar utils  #
LIBPIPEX = libpipex.a
#=====================================#

# Compiladores y flags    ==========================================================#
CC = cc
LIBCC = ar rcs
CFLAGS = -Wall -Werror -Wextra -g
INCFLAGS = -I$(PRINTHEAD) -I$(LIBHEADER) -I$(SOURCEPATH)
MEMORYFLAGS = -g -fsanitize=address,undefined
VALFLAGS = valgrind --leak-check=full --show-leak-kinds=all  --trace-children=yes -s
#===================================================================================#

#variables de entorno #
sani = 0
val = 0
#=====================#

# Reglas del makefile
all : run	


PRINTLIB :
ifeq ($(sani), 0)
	@echo "$(MAGENTA)Run mode without memory flags$(RESET)"
endif
ifeq ($(val), 0)
	@echo "$(MAGENTA)Run mode without valgrind$(RESET)"
endif
	@echo "$(YELLOW)Compiling PRINTLIB...$(RESET)"
	@make -s -C $(PRINT)
	@cp $(PRINT)/libftprintf.a .
	@mv libftprintf.a $(LIBPIPEX)
	
$(RMDIR):
	@mkdir -p $(RMDIR)

$(RMDIR)/%.o : $(SOURCEPATH)/%.c | $(RMDIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(YELLOW)Compiling $< to $@$(RESET)"

$(LIBPIPEX) : PRINTLIB $(OBJ)
	@$(LIBCC) $(LIBPIPEX) $(OBJ)

VALGRIND_ON :
	@echo "$(MAGENTA)MODO VALGRIND ACTIVADO$(RESET)"
	@$(MAKE) -s val=1 

FSANITAZE_ON :
	@echo "$(MAGENTA)MODO FSANITAZE ACTIVADO$(RESET)"
	@$(MAKE) -s sani=1

run : $(LIBPIPEX)
ifeq ($(sani),1)
	@$(CC) $(CFLAGS) $(INCFLAGS) $(MEMORYFLAGS) $(MYPROG) $(LIBPIPEX) -o pipex
else
	@$(CC) $(CFLAGS) $(INCFLAGS) $(MYPROG) $(LIBPIPEX) -o pipex
endif
ifeq ($(val),1)
	$(VALFLAGS) ./pipex Makefile cat cat salida.txt
else
	@ ./pipex Makefile cat cat salida.txt
endif
	@echo "$(GREEN)"
	@echo " _____    ____   ___   __   _____     ____   __  ____   _____  ___    ___  "
	@echo "|  _  \  / __ \ |   \ |  | |  ___|   |  _ \ |  ||  _ \ |  ___| \  \  /  /  "
	@echo "| | |  || |  | ||    \|  | | |___    | |_| ||  || |_| || |___   \  \/  /   "
	@echo "| |_|  || |__| ||  |\    | | |___    | ____/|  || ____/| |___   /  /\  \   "
	@echo "|_____/  \____/ |__| \___| |_____|   |_|    |__||_|    |_____| /__/  \__\  "
	@echo " $(RESET)"

clean :
	@make clean -s -C $(PRINT)
	@rm -rf $(RMDIR)

fclean : clean
	@echo "$(RED)DELETE FOLDER SYSTEM 32 (*ç*)$(RESET)"
	@make fclean -s -C $(PRINT)
	@rm -fr $(LIBPIPEX)
	@rm -fr pipex
	@rm -fr *.txt

re : fclean all

.PHONY: all clean fclean run re
