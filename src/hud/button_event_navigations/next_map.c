/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 04:32:03 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 15:54:40 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include "strings.h"
#include "string.h"

static char	*get_map_file(char *map_name, t_map_file *files)
{
	int	i;

	if (!map_name || !files)
		return (NULL);
	i = 0;
	while (files[i].file)
	{
		if (strncmp(files[i].file, map_name, strlen(map_name)) == 0)
			return (files[i].file);
		i++;
	}
	return (NULL);
}

void	next_map(t_main *g)
{
	char	*map_file;

	map_file = get_map_file(g->map.next_map, g->map.files);
	if (map_file)
	{
		reset_game(g, 0);
		if (load_map(map_file, g))
		{
			g->state = MENU_ERROR;
			return ;
		}
		init_minimap(g);
		create_objects_dynamic(g);
		clear_section(TEMPORARY);
		g->state = GAME;
		g->key_list.f3.key_switch = true;
	}
	else
		g->state = MENU_SUMMARY;
}
