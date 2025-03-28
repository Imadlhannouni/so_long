/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:51:58 by ilhannou          #+#    #+#             */
/*   Updated: 2025/03/02 17:31:53 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->rows)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
}

static void	destroy_textures(t_map *map)
{
	if (map->textures.wall)
		mlx_destroy_image(map->mlx, map->textures.wall);
	if (map->textures.floor)
		mlx_destroy_image(map->mlx, map->textures.floor);
	if (map->textures.player)
		mlx_destroy_image(map->mlx, map->textures.player);
	if (map->textures.collectible)
		mlx_destroy_image(map->mlx, map->textures.collectible);
	if (map->textures.exit)
		mlx_destroy_image(map->mlx, map->textures.exit);
	if (map->textures.playeri2)
		mlx_destroy_image(map->mlx, map->textures.playeri2);
	if (map->textures.playeri)
		mlx_destroy_image(map->mlx, map->textures.playeri);
}

int	close_game(t_map *map, int flag)
{
	if (flag == 0)
		mlx_destroy_window(map->mlx, map->window);
	destroy_textures(map);
	if (map->mlx)
	{
		mlx_destroy_display(map->mlx);
		free(map->mlx);
	}
	free_map(map);
	exit(0);
}
