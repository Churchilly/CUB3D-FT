/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 05:33:47 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/21 04:47:59 by yusudemi         ###   ########.fr       */
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

static int	check_map_materials(t_map *map, t_main *g)
{
	if (!map->texture_no.img || !map->texture_so.img
		|| !map->texture_we.img || !map->texture_ea.img)
		return (1);
	if (!map->texture_f.img)
		return (1);
	if (map->color_c == 0)
		return (1);
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
		if (current_id == NO)
		{
			if (load_texture(raw_map, &g->map.texture_no, "NO", g))
				return (1);
		}
		else if (current_id == SO)
			load_texture(raw_map, &g->map.texture_so, "SO", g);
		else if (current_id == WE)
			load_texture(raw_map, &g->map.texture_we, "WE", g);
		else if (current_id == EA)
			load_texture(raw_map, &g->map.texture_ea, "EA", g);
		else if (current_id == FL)
			load_texture(raw_map, &g->map.texture_f, "FL", g);
		else if (current_id == C)
			load_color(raw_map, &g->map.color_c, "C", g);
		else if (current_id == NEXT)
			load_next_map_info(raw_map, g);
		else
			break ;
		while (*raw_map && *raw_map != '\n')
			raw_map++;
	}
	if (check_map_materials(&g->map, g))
		return (1);
	load_doors(map_start);
	if (load_matrix(map_start, g))
		return (1);
	return (0);
}

static void debug(t_main *game);

int	load_map(char *map_file, t_main *game)
{
	char	*raw_map;
	char	*map_start;
	int		current_id;

	raw_map = read_file(map_file);
	if (!raw_map)
		return (1);
	if (map_parse(raw_map, game))
		return (1);
	return (0);
}






static void debug(t_main *game)
{
	printf("color_c::%d\n", game->map.color_c);
	// matrix
	printf("matrix::\n");
	int i = -1;
	while (game->map.matrix[++i])
	{
		int j = -1;
		while (game->map.matrix[i][++j])
		{
			printf("%c", game->map.matrix[i][j]);	
		}
		printf("\n");
	}
	//player
	printf("player_x::%f\nplayer_y::%f\n", game->map.player.pos.x, game->map.player.pos.y);
	printf("player_dov::%f\n", game->map.player.dov);
}