/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_objects_queue_add.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:30:49 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 22:01:51 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

void	queue_add_fireball(t_obj_node *node, t_main *g)
{
	t_fireball	*fireball;

	fireball = (t_fireball *)node->object;
	if (fireball->state == F_IDLE)
		return ;
	update_object_segment(&(fireball->segment), (fireball)->position,
		&g->map.player, FIREBALL_WIDTH);
	if (is_segment_in_fov(&g->map.player, &(fireball->segment)))
		add_to_render_queue(&g->objects, node, &g->map.player);
}

void	queue_add_enemy(t_obj_node *node, t_main *g)
{
	t_enemy	*enemy;

	enemy = (t_enemy *)node->object;
	if (enemy->state == E_IDLE)
		return ;
	update_object_segment(&(enemy->segment), enemy->position, &g->map.player,
		ENEMY_WIDTH);
	if (is_segment_in_fov(&g->map.player, &(enemy->segment)))
		add_to_render_queue(&g->objects, node, &g->map.player);
}

void	queue_add_particle(t_obj_node *node, t_main *g)
{
	t_fire_particle	*particle;

	particle = (t_fire_particle *)node->object;
	if (!particle->active)
		return ;
	update_object_segment(&(particle->segment), particle->position,
		&g->map.player, FIREBALL_WIDTH);
	if (is_segment_in_fov(&g->map.player, &(particle->segment)))
		add_to_render_queue(&g->objects, node, &g->map.player);
}

void	queue_add_door(t_obj_node *node, t_main *g)
{
	t_door	*door;

	door = (t_door *)node->object;
	if (is_segment_in_fov(&g->map.player, &(door->barrier)))
		add_to_render_queue(&g->objects, node, &g->map.player);
}

void	queue_add_orb(t_obj_node *node, t_main *g)
{
	t_orb	*orb;

	orb = (t_orb *)node->object;
	update_object_segment(&(orb->segment), orb->position, &g->map.player,
		ORB_WIDTH);
	if (is_segment_in_fov(&g->map.player, &(orb->segment)))
		add_to_render_queue(&g->objects, node, &g->map.player);
}
