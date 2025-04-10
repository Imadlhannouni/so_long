/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:49:06 by ilhannou          #+#    #+#             */
/*   Updated: 2025/03/20 20:34:47 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

char	**parse_to_map(char *file, t_map2 *map)
{
	char	**grid;
	char	*line;
	int		fd;
	int		i;

	if (count_rows(file, map) == -1)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit((perror("Error"), 1));
	grid = malloc(sizeof(char *) * (map->rows + 1));
	if (!grid)
		return (close(fd), NULL);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		grid[i++] = line;
		line = get_next_line(fd);
	}
	grid[i] = NULL;
	return (free(line), close(fd), grid);
}

static void	is_valid(t_map2 *map, int i, int j)
{
	if (map->grid[i][j] == 'C')
		map->collectible++;
	else if (map->grid[i][j] == 'E')
	{
		map->exit_x = j;
		map->exit_y = i;
		map->exit++;
	}
	else if (map->grid[i][j] == 'P')
	{
		map->player_x = j;
		map->player_y = i;
		map->player++;
	}
}

static int	add_to_map(t_map2 *map, int i)
{
	int (j);
	while (++i < map->rows)
	{
		j = 0;
		while (++j < map->cols)
		{
			is_valid(map, i, j);
			if (map->grid[i][j] != '1' && map->grid[i][j] != '0'
					&& map->grid[i][j] != 'P' && map->grid[i][j] != 'C'
						&& map->grid[i][j] != 'E' && map->grid[i][j] != 'X')
				return (write(1, "Error: Invalid characters\n", 26), 0);
		}
	}
	return (1);
}

static int	checksides(t_map2 *map)
{
	int	i;

	i = 0;
	while (i < map->rows)
	{
		if (map->grid[i][0] != '1' || map->grid[i][map->cols - 1] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < map->cols)
	{
		if (map->grid[0][i] != '1' || map->grid[map->rows - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	if (!add_to_map(map, i))
		return (0);
	if (map->player != 1 || map->exit != 1 || map->collectible < 1)
		return (0);
	return (1);
}

int	validate_map(t_map2 *map)
{
	int	i;

	map->cols = ft_strlen(map->grid[0]) - 1;
	if (map->cols == map->rows)
		return (0);
	i = 0;
	while (i < map->rows)
	{
		if (i < map->rows - 1)
		{
			if ((ft_strlen(map->grid[i]) - 1) != (unsigned long)map->cols)
				return (write(1, "Error: Invalid sides\n", 21), 0);
		}
		else
		{
			if ((ft_strlen(map->grid[i])) != (unsigned long)map->cols)
				return (write(1, "Error: Invalid sides\n", 21), 0);
		}
		i++;
	}
	if (!checksides(map))
		return (0);
	return (1);
}
