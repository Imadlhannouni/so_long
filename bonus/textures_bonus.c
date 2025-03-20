/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:50:46 by ilhannou          #+#    #+#             */
/*   Updated: 2025/03/20 20:35:37 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	load_textures(void *mlx, t_textures2 *t, t_map2 *map)
{
	int	w;
	int	h;

	w = 64;
	h = 64;
	t->floor = mlx_xpm_file_to_image(mlx, "textures/floor.xpm", &w, &h);
	t->exit = mlx_xpm_file_to_image(mlx, "textures/exit.xpm", &w, &h);
	t->player = mlx_xpm_file_to_image(mlx, "textures/player.xpm", &w, &h);
	t->playeri = mlx_xpm_file_to_image(mlx, "textures/playeri.xpm", &w, &h);
	t->playeri2 = mlx_xpm_file_to_image(mlx, "textures/playeri2.xpm", &w, &h);
	t->enemy = mlx_xpm_file_to_image(mlx, "textures/enemy.xpm", &w, &h);
	t->enemy2 = mlx_xpm_file_to_image(mlx, "textures/enemy2.xpm", &w, &h);
	t->wall = mlx_xpm_file_to_image(mlx, "textures/wall.xpm", &w, &h);
	t->collectible = mlx_xpm_file_to_image(mlx,
			"textures/collectible.xpm", &w, &h);
	if (!t->wall || !t->floor || !t->exit || !t->player || !t->collectible
		|| !t->playeri || !t->playeri2 || !t->enemy || !t->enemy2)
	{
		perror("Error");
		close_game(map, 1);
	}
}

void	update_animation(t_map2 *map)
{
	if (map->is_moving == 0)
	{
		map->frame_counter++;
		if (map->frame_counter >= 1000)
			map->frame_counter = 0;
	}
}

static void	render_px(t_map2 *m, t_textures2 *t, int x, int y)
{
	if (m->grid[y][x] == 'P')
	{
		if (m->frame_counter < 600)
			mlx_put_image_to_window(m->mlx, m->window,
				t->player, x * 64, y * 64);
		else
		{
			if (m->looking == 0)
				mlx_put_image_to_window(m->mlx, m->window,
					t->playeri, x * 64, y * 64);
			else
				mlx_put_image_to_window(m->mlx, m->window,
					t->playeri2, x * 64, y * 64);
		}
	}
	else if (m->grid[y][x] == 'X')
	{
		if (m->frame_counter < 600)
			mlx_put_image_to_window(m->mlx, m->window,
				t->enemy, x * 64, y * 64);
		else
			mlx_put_image_to_window(m->mlx, m->window,
				t->enemy2, x * 64, y * 64);
	}
}

void	render_map(void *mlx, void *w, t_map2 *map, t_textures2 *t)
{
	int (x), (y);
	y = 0;
	if (map->collectible == 0)
		map->grid[map->exit_y][map->exit_x] = 'E';
	while (y < map->rows)
	{
		x = 0;
		while (x < map->cols)
		{
			render_px(map, t, x, y);
			if (map->grid[y][x] == '1')
				mlx_put_image_to_window(mlx, w, t->wall, x * 64, y * 64);
			else if (map->grid[y][x] == 'C')
				mlx_put_image_to_window(mlx, w, t->collectible, x * 64, y * 64);
			else if (map->grid[y][x] == '0')
				mlx_put_image_to_window(mlx, w, t->floor, x * 64, y * 64);
			if (map->grid[y][x] == 'E' && map->collectible == 0)
				mlx_put_image_to_window(mlx, w, t->exit, x * 64, y * 64);
			else if (map->grid[y][x] == 'E')
				mlx_put_image_to_window(mlx, w, t->floor, x * 64, y * 64);
			x++;
		}
		y++;
	}
	display_mouv(map, map->mlx, map->window);
}
