/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 05:33:47 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/20 05:00:15 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <stdlib.h>
#include <stdio.h>  // Added: for printf function
#include "../../gc/gc.h"

static int	find_id(char *raw_map)
{
	if (raw_map[0] == 'N' && raw_map[1] == 'O' && is_space(raw_map[2]))
		return (NO);
	if (raw_map[0] == 'S' && raw_map[1] == 'O' && is_space(raw_map[2]))
		return (SO);
	if (raw_map[0] == 'W' && raw_map[1] == 'E' && is_space(raw_map[2]))
		return (WE);
	if (raw_map[0] == 'E' && raw_map[1] == 'A' && is_space(raw_map[2]))
		return (EA);
	if (raw_map[0] == 'F' && raw_map[1] == 'L' && is_space(raw_map[2]))
		return (FL);
	if (raw_map[0] == 'C' && is_space(raw_map[1]))
		return (C);
	if (raw_map[0] == 'N' && raw_map[1] == 'E' && raw_map[2] == 'X' 
		&& raw_map[3] == 'T' && is_space(raw_map[4]))
		return (NEXT);
	return (MAP);
}

static int	check_map_materials(t_map *map, t_main *g)
{
	if (!map->texture_no.img || !map->texture_so.img
		|| !map->texture_we.img || !map->texture_ea.img)
	{
		map_cleanup_exit("Error: Missing wall texture data", g);
		return (0);
	}
	if (!map->texture_f.img)
	{
		map_cleanup_exit("Error: Missing floor texture data", g);
		return (0);
	}
	if (map->color_c == 0)
	{
		map_cleanup_exit("Error: Missing ceiling color data", g);
		return (0);
	}
	return (1);
}

static void	map_parse(char *raw_map, t_main *g)
{
	int			current_id;
	char		*map_start;

	map_start = raw_map;
	while (*raw_map)
	{
		while (*raw_map && (is_space(*raw_map) || *raw_map == '\n'))
		{
			if (*raw_map == '\n')
				map_start = raw_map + 1;
			raw_map++;
		}
		if (*raw_map == '\0')
			break;
		current_id = find_id(raw_map);
		if (current_id == NO)
			load_texture(raw_map, &g->map.texture_no, "NO", g);
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
		if (g->state == MENU_ERROR)
			return ;
		while (*raw_map && *raw_map != '\n')
			raw_map++;
	}
	if (!check_map_materials(&g->map, g) || g->state == MENU_ERROR)
		return ;
	load_doors(raw_map);
	load_matrix(map_start, g);
}

void	load_map(char *map_file, t_main *game)
{
	char	*raw_map;

	map_cleanup(game);
	raw_map = read_file(map_file);
	if (!raw_map)
	{
		map_cleanup_exit("Error: Failed to read map file", game);
		return ;
	}
	map_parse(raw_map, game);
	if (game->state == MENU_ERROR)
		return ;
	// check textures one by one
	//test color
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
	// free(raw_map); HERE1
}
