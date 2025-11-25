/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_objects_list_operations.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 19:26:36 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/25 18:03:43 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <stddef.h>

void	add_object(t_obj_list *list, int type, void *obj, t_section sec)
{
	t_obj_node *new;

	new = alloc(sizeof(t_obj_node), sec);
	new->type = type;
	new->object = obj;
	new->next_render = NULL;
	if (sec == STATIC)
	{
		new->next = list->o_static;
		list->o_static = new;
	}
	else
	{
		new->next = list->o_dynamic;
		list->o_dynamic = new;
	}
}

static double	calculate_distance_object(t_player *player, t_obj_node *obj)
{
	double	dx;
	double	dy;
	t_door	*door;
	t_fireball *f;
	t_fire_particle *p;
	t_enemy			*e;
	t_orb			*orb;

	if (obj->type == DOOR)
	{
		door = (t_door *)obj->object;
		dx = (door->barrier.s.x + door->barrier.e.x) / 2.0 - player->pos.x;
		dy = (door->barrier.s.y + door->barrier.e.y) / 2.0 - player->pos.y;
	}
	else if (obj->type == FIREBALL)
	{
		f = (t_fireball *)obj->object;
		dx = (f->segment.s.x + f->segment.e.x) / 2.0 - player->pos.x;
		dy = (f->segment.s.y + f->segment.e.y) / 2.0 - player->pos.y;
	}
	else if (obj->type == PARTICLE)
	{
		p = (t_fire_particle *)obj->object;
		dx = (p->segment.s.x + p->segment.e.x) / 2.0 - player->pos.x;
		dy = (p->segment.s.y + p->segment.e.y) / 2.0 - player->pos.y;
	}
	else if (obj->type == ENEMY)
	{
		e = (t_enemy *)obj->object;
		dx = (e->segment.s.x + e->segment.e.x) / 2.0 - player->pos.x;
		dy = (e->segment.s.y + e->segment.e.y) / 2.0 - player->pos.y;
	}
	else if (obj->type == ORB)
	{
		orb = (t_orb *)obj->object;
		dx = (orb->segment.s.x + orb->segment.e.x) / 2.0 - player->pos.x;
		dy = (orb->segment.s.y + orb->segment.e.y) / 2.0 - player->pos.y;
	}
	else
	{
		dx = 0;
		dy = 0;
	}
	return (dx * dx + dy * dy);
}

void	add_to_render_queue(t_obj_list *list, t_obj_node *object, t_player *player)
{
	t_obj_node	*curr;
	t_obj_node	*prev;

	object->distance = calculate_distance_object(player, object);
	object->next_render = NULL;
	if (!list->to_render || object->distance > list->to_render->distance)
	{
		object->next_render = list->to_render;
		list->to_render = object;
		return ;
	}
	prev = NULL;
	curr = list->to_render;
	while (curr && curr->distance >= object->distance)
	{
		prev = curr;
		curr = curr->next_render;
	}
	object->next_render = curr;
	prev->next_render = object;
}

void	clear_render_queue(t_obj_list *list)
{
	t_obj_node *curr;
	t_obj_node *next;

	curr = list->to_render;
	while (curr)
	{
		next = curr->next_render;
		curr->next_render = NULL;
		curr->distance = -1.0;
		curr = next;
	}
	list->to_render = NULL;
}
