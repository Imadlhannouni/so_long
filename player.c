/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:00:00 by ilhannou          #+#    #+#             */
/*   Updated: 2025/03/21 20:11:17 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display_mouv(int i)
{
	write(1, "Mouvements : ", 13);
	ft_putnbr_fd(i, 1);
	write(1, "\r", 1);
}

void	move_player(t_map *map, int dx, int dy)
{
	int (new_x), (new_y);
	new_x = map->player_x + dx;
	new_y = map->player_y + dy;
	if (new_x < 0 || new_x >= map->cols || new_y < 0 || new_y >= map->rows)
		return ;
	if (map->grid[new_y][new_x] == '1')
		return ;
	map->mouvements++;
	if (map->grid[new_y][new_x] == 'C')
	{
		map->collectible--;
		map->grid[new_y][new_x] = '0';
	}
	if (map->grid[new_y][new_x] == 'E')
	{
		if (map->collectible == 0)
			close_game(map, 0);
	}
	display_mouv(map->mouvements);
	player_update(map, new_x, new_y);
}

static void	update_player_texture(t_map *map, int direction)
{
	int	width;
	int	height;

	width = 64;
	height = 64;
	if (direction == -1)
	{
		mlx_destroy_image(map->mlx, map->textures.player);
		map->textures.player = mlx_xpm_file_to_image(map->mlx,
				"textures/player2.xpm", &width, &height);
		map->looking = 1;
	}
	else if (direction == 1)
	{
		mlx_destroy_image(map->mlx, map->textures.player);
		map->textures.player = mlx_xpm_file_to_image(map->mlx,
				"textures/player.xpm", &width, &height);
		map->looking = 0;
	}
}

int	handle_keypress(int keycode, t_map *map)
{
	if (keycode == 119 || keycode == 65362)
		move_player(map, 0, -1);
	else if (keycode == 115 || keycode == 65364)
		move_player(map, 0, 1);
	else if (keycode == 97 || keycode == 65361)
	{
		update_player_texture(map, -1);
		move_player(map, -1, 0);
	}
	else if (keycode == 100 || keycode == 65363)
	{
		update_player_texture(map, 1);
		move_player(map, 1, 0);
	}
	else if (keycode == 65307)
	{
		if (map->mouvements != 0)
			write(1, "\n", 1);
		close_game(map, 0);
		return (0);
	}
	render_map(map->mlx, map->window, map, &map->textures);
	return (0);
}

void	setup_hooks(t_map *map)
{
	mlx_hook(map->window, 2, 1L << 0, handle_keypress, map);
	mlx_hook(map->window, 17, 0, close_game, map);
}
