/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 08:48:09 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/21 03:28:11 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <stdlib.h>
#include <stdio.h>

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

	copy = alloc(sizeof(char *) * (height + 1), TEMPORARY);
	i = -1;
	while (matrix[++i])
	{
		j = -1;
		while (matrix[i][++j])
			;
		copy[i] = alloc(sizeof(char) * (j + 1), TEMPORARY);
		j = -1;
		while (matrix[i][++j])
			copy[i][j] = matrix[i][j];
	}
	return (copy);
}

static int	check_map_enclosed(char **matrix, t_main *g)
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
					return (1);
			}
		}
	}
	return (0);
}

int	load_matrix(char *raw_map, t_main *g)
{
	int 	matrix_height;
	char	**copy;

	if (!*raw_map)
		return (1);
	matrix_height = create_matrix(raw_map, g);
	if (matrix_height == -1)
		return (1);
	copy = copy_matrix(g->map.matrix, matrix_height);
	if (check_map_enclosed(copy, g))
		return (1);
	return (0);
}
