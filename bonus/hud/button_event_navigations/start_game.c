/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 03:54:42 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/24 02:00:52 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

static void	reset(t_main *g)
{
	clear_section(DYNAMIC);
	g->map.player.pos.x = -1;
	g->map.player.pos.y = -1;
	g->map.player.mana = MAX_MANA;
	g->map.player.health = MAX_HEALTH;
	g->map.next_map = NULL;
	g->map.color_c = -1;
	g->map.texture_ea.img = NULL;
	g->map.texture_no.img = NULL;
	g->map.texture_ea.img = NULL;
	g->map.texture_ea.img = NULL;
	g->map.texture_f.img = NULL;
	g->map.map_timer = -1;
}

void	new_game(t_main *g, char *map_file)
{
	reset(g);
	if (load_map(map_file, g))
	{
		g->state = MENU_ERROR;
		return ;
	}
	else
		init_minimap(g);
	create_barriers(g);
	g->state = GAME;
	if (g->main_menu.btn_continue.height == -1)
	{
		set_button(&g->main_menu.btn_continue,
			&g->gallery.mmenu_start_btn,
			(t_vector){(WIN_WIDTH / 2
				- g->gallery.mmenu_start_btn.width / 4),
			(WIN_HEIGHT / 2) - (g->gallery.mmenu_start_btn.height * 2)
			/ 3 - g->gallery.mmenu_start_btn.height});
	}
	g->key_list.f3.key_switch = true;
}

char	*get_map_file(char *map_name, t_map_file *files)
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
		new_game(g, map_file);
	else
		g->state = MENU_SUMMARY;
}
