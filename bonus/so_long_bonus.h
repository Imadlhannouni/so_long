/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:16:31 by ilhannou          #+#    #+#             */
/*   Updated: 2025/02/28 17:28:35 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include "/usr/include/minilibx-linux/mlx.h"

typedef struct a_textures
{
	void	*wall;
	void	*floor;
	void	*player;
	void	*playeri;
	void	*playeri2;
	void	*enemy;
	void	*enemy2;
	void	*collectible;
	void	*exit;
}	b_textures;

typedef struct a_map
{
	void		*mlx;
	void		*window;
	char		**grid;
	int			cols;
	int			rows;
	int			player_x;
	int			player_y;
	int			player;
	int			collectible;
	int			exit_x;
	int			exit_y;
	int			enemy;
	int			exit;
	int			mouvements;
	int			is_moving;
	int			frame_counter;
	int			looking;
	b_textures	textures;
}	b_map;

char	**parse_to_map(char *file, b_map *map);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
int		validate_map(b_map *map);
void	free_map(b_map *map);
void	load_textures(void *mlx, b_textures *t, b_map *map);
void	render_map(void *mlx, void *w, b_map *map, b_textures *t);
int		valid_path(b_map *map);
int		close_game(b_map *map, int flag);
void	setup_hooks(b_map *map);
void	ft_putnbr_fd(int n, int fd);
void	display_mouv(b_map *map, void *mlx_ptr, void *win_ptr);
void	update_animation(b_map *map);
void	player_update(b_map *map, int new_x, int new_y);
int		count_rows(char *file, b_map *map);
void	error_handling(b_map *map);

#endif
