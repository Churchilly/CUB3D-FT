/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_list_operations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 19:26:36 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 20:54:29 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <stddef.h>

void	add_object(t_obj_list *list, int type, void *obj, t_section sec)
{
	t_obj_node	*new;

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

static t_vector	calculate_distance_object2(t_player *player, t_obj_node *obj)
{
	t_vector		delta;
	t_fire_particle	*p;
	t_enemy			*e;
	t_orb			*orb;

	delta = (t_vector){0, 0};
	if (obj->type == PARTICLE)
	{
		p = (t_fire_particle *)obj->object;
		delta.x = (p->segment.s.x + p->segment.e.x) / 2.0 - player->pos.x;
		delta.y = (p->segment.s.y + p->segment.e.y) / 2.0 - player->pos.y;
	}
	else if (obj->type == ENEMY)
	{
		e = (t_enemy *)obj->object;
		delta.x = (e->segment.s.x + e->segment.e.x) / 2.0 - player->pos.x;
		delta.y = (e->segment.s.y + e->segment.e.y) / 2.0 - player->pos.y;
	}
	else if (obj->type == ORB)
	{
		orb = (t_orb *)obj->object;
		delta.x = (orb->segment.s.x + orb->segment.e.x) / 2.0 - player->pos.x;
		delta.y = (orb->segment.s.y + orb->segment.e.y) / 2.0 - player->pos.y;
	}
	return (delta);
}

static double	calculate_distance_object(t_player *player, t_obj_node *obj)
{
	t_vector	delta;
	t_door		*door;
	t_fireball	*f;

	delta = (t_vector){0, 0};
	if (obj->type == DOOR)
	{
		door = (t_door *)obj->object;
		delta.x = (door->barrier.s.x + door->barrier.e.x) / 2.0 - player->pos.x;
		delta.y = (door->barrier.s.y + door->barrier.e.y) / 2.0 - player->pos.y;
	}
	else if (obj->type == FIREBALL)
	{
		f = (t_fireball *)obj->object;
		delta.x = (f->segment.s.x + f->segment.e.x) / 2.0 - player->pos.x;
		delta.y = (f->segment.s.y + f->segment.e.y) / 2.0 - player->pos.y;
	}
	else
	{
		delta = calculate_distance_object2(player, obj);
	}
	return (delta.x * delta.x + delta.y * delta.y);
}

void	add_to_render_queue(t_obj_list *list, t_obj_node *object,
		t_player *player)
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
	t_obj_node	*curr;
	t_obj_node	*next;

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
