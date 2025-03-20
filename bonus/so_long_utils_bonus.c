/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:17:47 by ilhannou          #+#    #+#             */
/*   Updated: 2025/03/20 20:35:07 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}

void	player_update(t_map2 *map, int new_x, int new_y)
{
	map->grid[map->player_y][map->player_x] = '0';
	map->player_x = new_x;
	map->player_y = new_y;
	map->grid[new_y][new_x] = 'P';
}

int	count_rows(char *file, t_map2 *map)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit((perror("Error"), 1));
	line = get_next_line(fd);
	while (line != NULL)
	{
		map->rows++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	if (map->rows == 0)
		return (-1);
	return (0);
}

void	error_handling(t_map2 *map)
{
	if (!map->grid)
	{
		write(2, "Error: Invalid Parsing\n", 23);
		exit(1);
	}
	if (!validate_map(map) || !valid_path(map))
	{
		write(2, "Error: Invalid map or path\n", 27);
		free_map(map);
		exit(1);
	}
}
