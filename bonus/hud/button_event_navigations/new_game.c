/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 03:54:42 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 22:22:22 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include "string.h"

void	new_game(t_main *g, char *map_file)
{
	reset_game(g, 1);
	if (load_map(map_file, g))
	{
		g->state = MENU_ERROR;
		return ;
	}
	init_minimap(g);
	create_objects_dynamic(g);
	clear_section(TEMPORARY);
	g->map.player.healing = SPAWN_HEALING;
	g->state = GAME;
	g->key_list.f3.key_switch = true;
}
