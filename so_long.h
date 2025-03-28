/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:50:36 by ilhannou          #+#    #+#             */
/*   Updated: 2025/03/20 19:29:13 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include "/usr/include/minilibx-linux/mlx.h"

typedef struct s_textures
{
	void	*wall;
	void	*floor;
	void	*player;
	void	*playeri;
	void	*playeri2;
	void	*collectible;
	void	*exit;
}	t_textures;

typedef struct s_map
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
	int			exit;
	int			mouvements;
	int			is_moving;
	int			frame_counter;
	int			looking;
	t_textures	textures;
}	t_map;

char	**parse_to_map(char *file, t_map *map);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
int		validate_map(t_map *map);
void	free_map(t_map *map);
void	load_textures(void *mlx, t_textures *t, t_map *map);
void	render_map(void *mlx, void *w, t_map *map, t_textures *t);
int		valid_path(t_map *map);
int		close_game(t_map *map, int flag);
void	setup_hooks(t_map *map);
void	ft_putnbr_fd(int n, int fd);
void	display_mouv(int i);
void	player_update(t_map *map, int new_x, int new_y);
int		count_rows(char *file, t_map *map);
void	error_handling(t_map *map);

#endif
