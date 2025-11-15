/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_objects_list_operations.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 19:26:36 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/15 18:05:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <stddef.h>

void	add_object(t_obj_list *list, int type, void *obj)
{
	t_obj_node *new;

	new = malloc(sizeof(t_obj_node)); // alloc_crit
	new->type = type;
	new->object = obj;
	new->next = NULL;
	new->next_render = NULL;
	new->next = list->all;
	list->all = new;
}

static double	calculate_distance_object(t_player *player, t_obj_node *obj)
{
	double	dx;
	double	dy;
	t_door	*door;
	t_fireball *f;

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

	if (object->type)
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
