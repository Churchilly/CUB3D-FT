/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 05:20:00 by root              #+#    #+#             */
/*   Updated: 2025/11/22 05:37:28 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hud.h"
#include "../../main/main.h"

static void	write_image_to_image(t_cub3_image *dst, t_cub3_image *src,
	int x, int y)
{
	int	sx;
	int	sy;
	int	color;

	sy = 0;
	while (sy < src->height)
	{
		sx = 0;
		while (sx < src->width)
		{
			color = src->image[sy * src->width + sx];
			if ((unsigned int)color != 0xffffffff)
				dst->image[(y + sy) * dst->width + (x + sx)] = color;
			sx++;
		}
		sy++;
	}
}

static int	get_map_width(char **matrix)
{
	int	max_width;
	int	curr_width;
	int	i;

	max_width = 0;
	i = 0;
	while (matrix[i])
	{
		curr_width = 0;
		while (matrix[i][curr_width])
			curr_width++;
		if (curr_width > max_width)
			max_width = curr_width;
		i++;
	}
	return (max_width);
}

static int	get_map_height(char **matrix)
{
	int	height;

	height = 0;
	while (matrix[height])
		height++;
	return (height);
}

void	init_minimap(t_main *g)
{
	int	map_x;
	int	map_y;
	int	map_width;
	int	map_height;

	map_width = get_map_width(g->map.matrix);
	map_height = get_map_height(g->map.matrix);
	g->minimap_full.width = map_width * MMAP_GRID_SIZE;
	g->minimap_full.height = map_height * MMAP_GRID_SIZE;
	g->minimap_full.image = alloc(g->minimap_full.width
			* g->minimap_full.height * sizeof(int), STATIC);
	map_y = 0;
	while (map_y < map_height)
	{
		map_x = 0;
		while (map_x < map_width && g->map.matrix[map_y][map_x])
		{
			if (g->map.matrix[map_y][map_x] == '1')
				write_image_to_image(&g->minimap_full, &g->gallery.mmap.wall,
					map_x * MMAP_GRID_SIZE, map_y * MMAP_GRID_SIZE);
			else if (g->map.matrix[map_y][map_x] == '0')
				write_image_to_image(&g->minimap_full, &g->gallery.mmap.floor,
					map_x * MMAP_GRID_SIZE, map_y * MMAP_GRID_SIZE);
			map_x++;
		}
		map_y++;
	}
}
