/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 08:07:31 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/24 09:55:43 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE // delete it later its just for me .p
#include <stdlib.h>
#include <stdio.h>
#include "../../main/main.h"
#include <math.h>
#include <ctype.h>

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || isspace(c)
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == 'd' || c == 'D');
}

static int get_map_height(char *raw_map, t_main *g)
{
	int	count;
	int	ret;

	count = 1;
	ret = 0;
	(void)g;
	while (*raw_map)
	{
		if (*raw_map == '\n')
			count++;
		else if (!is_valid_map_char(*raw_map))
			return (-1);
		else
			ret = count;
		raw_map++;
	}
	return (ret);
}

static int	char_to_int(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (48);
	else if (c == '1')
		return (49);
	else if (c == 'd' || c == 'D')
		return (68);
	else if (isspace(c))
		return (50);
	return (83);
}

void	parse_player_view(t_main *g, char direction)
{
	if (direction == 'E')
		g->map.player.dov = 0; // 0degrees,
	if (direction == 'S')
		g->map.player.dov = M_PI / 2; // 90 d
	if (direction == 'W')
		g->map.player.dov = M_PI; // 180 d
	if (direction == 'N')
		g->map.player.dov = 3 * M_PI / 2; // 270d
}

static char	*create_map_line(char **raw_map, t_main *g)
{
	char	*matrix_line;
	int	i;
	int	line_len;

	line_len = 0;
	while ((*raw_map)[line_len] && (*raw_map)[line_len] != '\n')
		line_len++;
	matrix_line = alloc(sizeof(char) * (line_len + 1), DYNAMIC);
	i = -1;
	while (++i < line_len)
	{
		matrix_line[i] = char_to_int(**raw_map);
		if (**raw_map == 'N' || **raw_map == 'S'
			|| **raw_map == 'E' || **raw_map == 'W')
		{
			if (g->map.player.pos.x != -1)
				return (NULL);
			parse_player_view(g, **raw_map);
			g->map.player.pos.x = i + 0.5;
		}
		(*raw_map)++;
	}
	(*raw_map)++;
	return (matrix_line);
}

int	create_matrix(char *raw_map, t_main *g)
{
	int	matrix_height;
	int	player;
	int	i;

	matrix_height = get_map_height(raw_map, g);
	if (matrix_height == -1)
		return (-1);
	g->map.matrix = alloc(sizeof(char *) * (matrix_height + 1), DYNAMIC);
	i = -1;
	player = 0;
	while (++i < matrix_height)
	{
		g->map.matrix[i] = create_map_line(&raw_map, g);
		if (g->map.matrix[i] == NULL)
			return (-1);
		if (g->map.player.pos.x != -1 && !player)
		{
			player = 1;
			g->map.player.pos.y = i + 0.5;
		}
	}
	if (g->map.player.pos.x == -1)
		return (-1);
	return (matrix_height);
}
