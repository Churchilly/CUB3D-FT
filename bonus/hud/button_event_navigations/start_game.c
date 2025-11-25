/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 03:54:42 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/25 20:45:09 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include "string.h"
#include "strings.h"

static void reset_static_objects(t_main *g)
{
	t_obj_node	*curr;

	clear_render_queue(&g->objects);
	curr = g->objects.o_static;
	while (curr)
	{
		if (curr->type == FIREBALL)
		{
			t_fireball *fireball = curr->object;
			fireball->state = F_IDLE;
			fireball->position.x = -1.0;
			fireball->position.y = -1.0;
			fireball->direction = 0.0;
		}
		else if (curr->type == PARTICLE)
		{
			t_fire_particle *particle = curr->object;
			particle->active = false;
			particle->position.x = -1.0;
			particle->position.y = -1.0;
		}
		else if (curr->type == ENEMY)
		{
			t_enemy *enemy = curr->object;
			enemy->health = ENEMY_HEALTH;
			enemy->state = IDLE;
			enemy->position.x = -1.0;
			enemy->position.y = -1.0;
			enemy->red_alpha = 0.0;
			enemy->attack_time_log = 0;
		}
		curr = curr->next;
	}
}

static void	reset(t_main *g, int all)
{
	if (all)
	{
		bzero(&g->record, sizeof(t_record));
		bzero(&g->map.player.inventory, sizeof(t_inventory));
	}
	reset_static_objects(g);
	clear_section(DYNAMIC);
	g->objects.o_dynamic = NULL;
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
	{
		reset(g, 0);
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
