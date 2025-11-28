/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 04:35:18 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 15:54:53 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include "string.h"

static void	reset_fireball(t_fireball *fireball)
{
	fireball->state = F_IDLE;
	fireball->position.x = -1.0;
	fireball->position.y = -1.0;
	fireball->direction = 0.0;
}

static void	reset_particle(t_fire_particle *particle)
{
	particle->active = false;
	particle->position.x = -1.0;
	particle->position.y = -1.0;
}

static void	reset_enemy(t_enemy *enemy)
{
	enemy->health = ENEMY_HEALTH;
	enemy->state = E_IDLE;
	enemy->position.x = -1.0;
	enemy->position.y = -1.0;
	enemy->red_alpha = 0.0;
	enemy->attack_time_log = 0;
}

static void	reset_static_objects(t_main *g)
{
	t_obj_node	*curr;

	curr = g->objects.o_static;
	while (curr)
	{
		if (curr->type == FIREBALL)
		{
			reset_fireball(curr->object);
		}
		else if (curr->type == PARTICLE)
		{
			reset_particle(curr->object);
		}
		else if (curr->type == ENEMY)
		{
			reset_enemy(curr->object);
		}
		curr = curr->next;
	}
}

void	reset_game(t_main *g, int all)
{
	if (all)
	{
		bzero(&g->record, sizeof(t_record));
		bzero(&g->map.player.inventory, sizeof(t_inventory));
		g->record.play_time = -1;
	}
	clear_render_queue(&g->objects);
	reset_static_objects(g);
	clear_section(DYNAMIC);
	g->spellbook.current = SPELL_FIREBALL;
	g->spellbook.cur_texture = &g->spellbook.texture_fireball;
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
