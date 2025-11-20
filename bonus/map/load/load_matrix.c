/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 08:48:09 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/20 02:09:01 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../gc/gc.h"

static int	flood_fill(char **matrix, int x, int y)
{
	int	up;
	int	down;
	int	left;
	int	right;

	if (y < 0 || !matrix[y] || x < 0 || matrix[y][x] == 0)
		return (0);
	if (matrix[y][x] == 49 || matrix[y][x] == 83)
		return (1);
	matrix[y][x] = 83;
	up = flood_fill(matrix, x, y - 1);
	down = flood_fill(matrix, x, y + 1);
	left = flood_fill(matrix, x - 1, y);
	right = flood_fill(matrix, x + 1, y);
	return (up && down && left && right);
}

static char	**copy_matrix(char **matrix, int height)
{
	char	**copy;
	int i;
	int j;

	copy = alloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = -1;
	while (matrix[++i])
	{
		j = -1;
		while (matrix[i][++j])
			;
		copy[i] = alloc(sizeof(char) * (j + 1));
		if (!copy)
			return (NULL);
		j = -1;
		while (matrix[i][++j])
			copy[i][j] = matrix[i][j];
		copy[i][j] = 0;
	}
	copy[i] = NULL;
	return (copy);
}

static void	check_map_enclosed(char **matrix, t_main *g)
{
	int	x;
	int	y;

	y = -1;
	while (matrix[++y])
	{
		x = -1;
		while (matrix[y][++x])
		{
			if (matrix[y][x] == '0')
			{
				if (!flood_fill(matrix, x, y))
					map_cleanup_exit("Error: Map is not properly enclosed by walls", g);
			}
		}
	}
}

void	load_matrix(char *raw_map, t_main *g)
{
	int 	matrix_height;
	char	**copy;

	if (!*raw_map)
	{
		map_cleanup_exit("Error: Missing map data", g);
		return ;
	}
	matrix_height = create_matrix(raw_map, g);
	if (g->state == MENU_ERROR)
		return ;
	// copy current matrix to make changes on it
	copy = copy_matrix(g->map.matrix, matrix_height);
	if (!copy)
	{
		map_cleanup_exit("Error: Memory allocation failed", g);
		return ;
	}
	check_map_enclosed(copy, g);
}
