/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhannou <ilhannou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:20:12 by ilhannou          #+#    #+#             */
/*   Updated: 2025/03/20 19:37:00 by ilhannou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	l;

	l = 0;
	i = 0;
	while (src[l] != '\0')
		l++;
	if (size == 0)
		return (l);
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (l);
}

static int	checkname(char *str)
{
	char	str2[5];

	int (i), (j);
	ft_strlcpy(str2, ".ber", 5);
	j = 3;
	i = ft_strlen(str) - 1;
	while (j >= 0)
	{
		if (str2[j] == str[i])
		{
			j--;
			i--;
		}
		else if (str2[j] != str[i] || i == 0)
			return (write(2, "Error: Invalide file name\n", 26), 0);
	}
	if (str[i] == '/')
		return (write(2, "Error: Invalide file name\n", 26), 0);
	while (i > 0)
	{
		if (str[i] == '.')
			return (write(2, "Error: Invalide file name\n", 26), 0);
		i--;
	}
	return (1);
}

static void	init_list(t_map *map)
{
	map->mouvements = 0;
	map->grid = NULL;
	map->is_moving = 0;
	map->frame_counter = 0;
	map->looking = 0;
	map->rows = 0;
	map->collectible = 0;
	map->player = 0;
	map->exit = 0;
}

int	main(int argc, char *argv[])
{
	t_map		map;
	int			i;

	i = 0;
	if (argc == 2 && checkname(argv[1]))
	{
		init_list(&map);
		map.grid = parse_to_map(argv[1], &map);
		error_handling(&map);
		map.mlx = mlx_init();
		if (!map.mlx)
			return (write(2, "Error: Failed\n", 26), free_map(&map), 1);
		load_textures(map.mlx, &map.textures, &map);
		map.window = mlx_new_window(map.mlx, map.cols * 64,
				map.rows * 64, "So Long");
		if (!map.window)
			return (perror("Error"), close_game(&map, 1), 1);
		setup_hooks(&map);
		render_map(map.mlx, map.window, &map, &map.textures);
		mlx_loop(map.mlx);
	}
	else if (argc != 2)
		write(2, "Error: Arguments Invalid\n", 25);
}
