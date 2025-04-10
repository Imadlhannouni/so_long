/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_valid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:46:01 by ilhannou          #+#    #+#             */
/*   Updated: 2025/03/21 20:09:26 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	is_valid_cell(t_map *map, int x,
		int y, bool **visited)
{
	return (x >= 0 && x < map->cols && y >= 0 && y < map->rows
		&& map->grid[y][x] != '1' && !visited[y][x]);
}

static void	flood_fill(t_map *map, int x,
		int y, bool **visited)
{
	if (!is_valid_cell(map, x, y, visited))
		return ;
	visited[y][x] = true;
	flood_fill(map, x + 1, y, visited);
	flood_fill(map, x - 1, y, visited);
	flood_fill(map, x, y + 1, visited);
	flood_fill(map, x, y - 1, visited);
}

static void	count(t_map *map, bool **visited,
		int *collectible, int *exit)
{
	int (i), (j);
	j = 0;
	while (j < map->rows)
	{
		i = 0;
		while (i < map->cols)
		{
			if (map->grid[j][i] == 'C' && visited[j][i] == true)
				(*collectible)++;
			else if (map->grid[j][i] == 'E' && visited[j][i] == true)
				(*exit) = 1;
			i++;
		}
		j++;
	}
}

static int	free_visited(bool **visited, int rows, int ret_val)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
	return (ret_val);
}

int	valid_path(t_map *map)
{
	bool	**visited;

	int (collectible), (exit), (i), (j);
	visited = malloc(sizeof(bool *) * map->rows);
	if (!visited)
		return (0);
	j = -1;
	while (++j < map->rows)
	{
		visited[j] = malloc(sizeof(bool) * map->cols);
		if (!visited[j])
			return (free_visited(visited, j, 0));
		i = -1;
		while (++i < map->cols)
			visited[j][i] = false;
	}
	flood_fill(map, map->player_x, map->player_y, visited);
	collectible = 0;
	exit = 0;
	count(map, visited, &collectible, &exit);
	free_visited(visited, map->rows, 1);
	if (collectible == map->collectible && exit == 1)
	return (write(1, "Error: characters blocked\n", 26), 1);
	return (0);
}
