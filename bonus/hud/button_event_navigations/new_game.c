/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 03:54:42 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 04:39:16 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include "string.h"

void	new_game(t_main *g, char *map_file)
{
	reset(g, 1);
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
