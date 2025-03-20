/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:16:31 by ilhannou          #+#    #+#             */
/*   Updated: 2025/03/20 20:35:34 by ilhannou         ###   ########.fr       */
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
}	t_textures2;

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
	t_textures2	textures;
}	t_map2;

char	**parse_to_map(char *file, t_map2 *map);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
int		validate_map(t_map2 *map);
void	free_map(t_map2 *map);
void	load_textures(void *mlx, t_textures2 *t, t_map2 *map);
void	render_map(void *mlx, void *w, t_map2 *map, t_textures2 *t);
int		valid_path(t_map2 *map);
int		close_game(t_map2 *map, int flag);
void	setup_hooks(t_map2 *map);
void	ft_putnbr_fd(int n, int fd);
void	display_mouv(t_map2 *map, void *mlx_ptr, void *win_ptr);
void	update_animation(t_map2 *map);
void	player_update(t_map2 *map, int new_x, int new_y);
int		count_rows(char *file, t_map2 *map);
void	error_handling(t_map2 *map);

#endif
