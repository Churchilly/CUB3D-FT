/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 05:33:47 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 16:36:01 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <stdlib.h>
#include <ctype.h>

#include <stdio.h> // for debug

static int	find_id(char *raw_map)
{
	if (raw_map[0] == 'N' && raw_map[1] == 'O' && isspace(raw_map[2]))
		return (NO);
	if (raw_map[0] == 'S' && raw_map[1] == 'O' && isspace(raw_map[2]))
		return (SO);
	if (raw_map[0] == 'W' && raw_map[1] == 'E' && isspace(raw_map[2]))
		return (WE);
	if (raw_map[0] == 'E' && raw_map[1] == 'A' && isspace(raw_map[2]))
		return (EA);
	if (raw_map[0] == 'F' && raw_map[1] == 'L' && isspace(raw_map[2]))
		return (FL);
	if (raw_map[0] == 'C' && isspace(raw_map[1]))
		return (C);
	if (raw_map[0] == 'N' && raw_map[1] == 'E' && raw_map[2] == 'X' 
		&& raw_map[3] == 'T' && isspace(raw_map[4]))
		return (NEXT);
	return (MAP);
}

static int	check_map_materials(t_map *map)
{
	printf("%p\n", map->texture_so.img);
	if (!map->texture_no.img)
		return (printf("dubletexture0\n"),1);
	if (!map->texture_so.img)
		return (printf("dubletexture1\n"),1);
	if (!map->texture_ea.img)
		return (printf("dubletexture2\n"),1);
	if (!map->texture_we.img)
		return (printf("dubletexture3\n"),1);
	if (!map->texture_f.img)
		return (printf("dubletexture4\n"),1);
	if (map->color_c == -1)
		return (printf("dublecolor\n"),1);
	return (printf("YAY?\n"),0);
}

static int	map_parse_material(char *raw_map, t_main *g, int id)
{
	if (id == NO && load_texture(raw_map, &g->map.texture_no, g))
		return (1);
	else if (id == SO && load_texture(raw_map, &g->map.texture_so, g))
		return (1);
	else if (id == WE && load_texture(raw_map, &g->map.texture_we, g))
		return (1);
	else if (id == EA && load_texture(raw_map, &g->map.texture_ea, g))
		return (1);
	else if (id == FL && load_texture(raw_map, &g->map.texture_f, g))
		return (1);
	else if (id == C && load_color(raw_map, &g->map.color_c))
		return (1);
	else if (id == NEXT)
		load_next_map_info(raw_map, g);
	return (0);
}

static void	skip_spaces(char **raw_map, char **map_start)
{
	while (**raw_map && isspace(**raw_map))
	{
		if (**raw_map == '\n')
			(*map_start) = (*raw_map) + 1;
		(*raw_map)++;
	}
}

static int	map_parse(char *raw_map, t_main *g)
{
	int			current_id;
	char		*map_start;

	map_start = raw_map;
	while (*raw_map)
	{
		skip_spaces(&raw_map, &map_start);
		if (*raw_map == '\0')
			break;
		current_id = find_id(raw_map);
		if (current_id == MAP)
			break ;
		if (map_parse_material(raw_map, g, current_id))
			return (1);
		while (*raw_map && *raw_map != '\n')
			raw_map++;
	}
	if (check_map_materials(&g->map))
		return (1);
	load_doors(map_start, g);
	if (load_matrix(map_start, g))
		return (1);
	return (0);
}

int	load_map(char *map_file, t_main *game)
{
	char	*raw_map;

	raw_map = read_file(map_file);
	if (!raw_map)
		return (1);
	if (map_parse(raw_map, game))
		return (1);
	return (0);
}
