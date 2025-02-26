# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/18 13:09:46 by ilhannou          #+#    #+#              #
#    Updated: 2025/02/26 14:24:54 by ilhannou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

OBJDIR = obj

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = free.c main.c map_parse.c path_valid.c player.c textures.c so_long_utils.c

OBJ = $(OBJDIR)/free.o $(OBJDIR)/main.o $(OBJDIR)/map_parse.o $(OBJDIR)/path_valid.o \
	$(OBJDIR)/player.o $(OBJDIR)/textures.o $(OBJDIR)/so_long_utils.o

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling the main project..."
	@$(CC) $(CFLAGS) -o $@ $^ -L/usr/include/minilibx-linux -lmlx_Linux -lX11 -lXext includes/get_next_line/get_next_line.c includes/get_next_line/get_next_line_utils.c
	@echo "Compilation complete!"

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJDIR)
	@echo "Cleaned object files!"

fclean: clean
	@echo "Removing executable and libraries..."
	@rm -rf $(NAME)
	@echo "All cleaned!"

re: fclean all

.PHONY: all bonus re clean fclean