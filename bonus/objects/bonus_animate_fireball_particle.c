/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_animate_fireball_particle.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:14:46 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/22 05:18:10 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

static void animate_particle_y(t_fire_particle *particle)
{
	if (particle->active)
	{
		if (particle->start_y >= 100)
		{
			particle->active = false;
			particle->start_y = 0;
		}
		else
			particle->start_y += 4;
	}
}

void animate_particles(t_main *g)
{
	static long long time_log = 0;
	long long curr_time;
	t_obj_node *obj;
	t_fire_particle *particle;

	curr_time = current_time_ms();
	if (curr_time - time_log > 50)
	{
		obj = g->objects.all;
		while (obj)
		{
			if (obj->type == PARTICLE)
			{
				particle = obj->object;
				animate_particle_y(particle);
			}
			obj = obj->next;
		}
		time_log = curr_time;
	}
}

void add_particle(t_main *g, t_fireball *f)
{
	static long long time_log = 0;
	long long curr_time;
	t_obj_node *obj;
	t_fire_particle *particle;
	
	curr_time = current_time_ms();
	if (curr_time - time_log > 300)
	{
		obj = g->objects.all;
		while (obj)
		{
			if (obj->type == PARTICLE)
			{
				particle = obj->object;
				if (!particle->active)
					break;
			}
			obj = obj->next;
		}
		particle->image = g->gallery.fireball_particle_1;
        particle->position = (t_vector){f->position.x, f->position.y};
		particle->segment = f->segment;
		particle->active = true;
		time_log = curr_time;
	}
}

