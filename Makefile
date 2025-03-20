# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/18 13:09:46 by ilhannou          #+#    #+#              #
#    Updated: 2025/03/02 20:25:44 by ilhannou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
BONUS_NAME = so_long_bonus

OBJDIR = obj

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = free.c main.c map_parse.c path_valid.c player.c textures.c so_long_utils.c
BONUS_SRC = bonus/free_bonus.c bonus/main_bonus.c bonus/map_parse_bonus.c bonus/path_valid_bonus.c bonus/player_bonus.c \
		bonus/textures_bonus.c bonus/so_long_utils_bonus.c

OBJ = $(OBJDIR)/free.o $(OBJDIR)/main.o $(OBJDIR)/map_parse.o $(OBJDIR)/path_valid.o \
	$(OBJDIR)/player.o $(OBJDIR)/textures.o $(OBJDIR)/so_long_utils.o

OBJ_BONUS = $(OBJDIR)/free_bonus.o $(OBJDIR)/main_bonus.o $(OBJDIR)/map_parse_bonus.o \
	$(OBJDIR)/path_valid_bonus.o $(OBJDIR)/player_bonus.o $(OBJDIR)/textures_bonus.o \
	$(OBJDIR)/so_long_utils_bonus.o

LIBS = -L/usr/include/minilibx-linux -lmlx_Linux -lX11 -lXext
GNL = includes/get_next_line/get_next_line.c includes/get_next_line/get_next_line_utils.c

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJ)
	@echo "Compiling the main project..."
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS) $(GNL)
	@echo "Compilation complete!"

$(BONUS_NAME): $(OBJ_BONUS)
	@echo "Compiling the bonus project..."
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS) $(GNL)
	@echo "Bonus compilation complete!"

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%_bonus.o: bonus/%_bonus.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir $(OBJDIR)

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJDIR)
	@echo "Cleaned object files!"

fclean: clean
	@echo "Removing executable and libraries..."
	@rm -f $(NAME) $(BONUS_NAME)
	@echo "All cleaned!"

re: fclean all

.PHONY: all bonus re clean fclean