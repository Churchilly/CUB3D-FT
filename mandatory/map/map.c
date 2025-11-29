/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 05:33:47 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/30 01:34:12 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <stdio.h>
#include <stdlib.h>

static int	find_id(char *raw_map)
{
	if (raw_map[0] == 'N' && raw_map[1] == 'O' && is_space(raw_map[2]))
		return (0);
	if (raw_map[0] == 'S' && raw_map[1] == 'O' && is_space(raw_map[2]))
		return (1);
	if (raw_map[0] == 'W' && raw_map[1] == 'E' && is_space(raw_map[2]))
		return (2);
	if (raw_map[0] == 'E' && raw_map[1] == 'A' && is_space(raw_map[2]))
		return (3);
	if (raw_map[0] == 'F' && is_space(raw_map[1]))
		return (4);
	if (raw_map[0] == 'C' && is_space(raw_map[1]))
		return (5);
	return (6);
}

static void	check_parsed_table(int parsed[6])
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (parsed[i] == 0)
		{
			printf("Error: Missing map material data\n");
			exit(1);
		}
		i++;
	}
}

static int	map_parse_material(int current_id, char **raw_map, int parsed[6],
		t_main *g)
{
	if (current_id < F)
	{
		parse_texture(*raw_map, current_id, parsed, g);
		while (**raw_map && **raw_map != '\n')
			(*raw_map)++;
	}
	else if (current_id < MAP)
	{
		parse_color(*raw_map, current_id, parsed, g);
		while (**raw_map && **raw_map != '\n')
			(*raw_map)++;
	}
	else
		return (-1);
	return (0);
}

static void	map_parse(char *raw_map, t_main *g)
{
	int			parsed[6];
	int			current_id;
	char		*map_start;

	map_start = raw_map;
	ft_bzero(parsed, 6 * sizeof(int));
	while (*raw_map)
	{
		while (*raw_map && (is_space(*raw_map) || *raw_map == '\n'))
		{
			if (*raw_map == '\n')
				map_start = raw_map + 1;
			raw_map++;
		}
		if (*raw_map == '\0')
			break ;
		current_id = find_id(raw_map);
		if (map_parse_material(current_id, &raw_map, parsed, g) == -1)
			break ;
	}
	check_parsed_table(parsed);
	parse_matrix(map_start, g);
}

void	cub_map(char *map_file, t_main *game)
{
	char	*raw_map;

	raw_map = cub_map_read(map_file);
	if (!raw_map)
		exit(1);
	map_parse(raw_map, game);
}
