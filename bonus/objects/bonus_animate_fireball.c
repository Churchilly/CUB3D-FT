/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_animate_fireball.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:14:46 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/19 21:32:05 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

static void animate_particles(t_main *g)
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
			obj = obj->next;
		}
		time_log = curr_time;
	}
}

static void add_particle(t_main *g, t_fireball *f)
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
		particle->position.x = f->position.x;
		particle->position.y = f->position.y;
		particle->segment = f->segment;
		particle->active = true;
		time_log = curr_time;
	}
}

static bool fireball_collision(t_vector *f_pos, t_main *g)
{
	t_obj_node *obj;
	t_enemy *enemy;

	if (g->map.matrix[(int)f_pos->y][(int)f_pos->x] == '1')
		return (true);
	obj = g->objects.all;
	while (obj)
	{
		if (obj->type == ENEMY)
		{
			enemy = (t_enemy *)obj->object;
			if (enemy->state == ALIVE)
			{
				if (enemy->position.x >= f_pos->x - ENEMY_WIDTH / 2 && enemy->position.x <= f_pos->x + ENEMY_WIDTH / 2
					&& enemy->position.y >= f_pos->y - ENEMY_WIDTH / 2 && enemy->position.y <= f_pos->y + ENEMY_WIDTH / 2)
					return (true);
			}
		}
		obj = obj->next;
	}
	return (false);
}

void	animate_fireball(t_fireball *f, t_main *g, t_cub3_gallery *gal)
{
	static long long time_log = 0;
	long long curr_time;

	animate_fireball_sprite(g);
	animate_fireball_particle_sprite(g);
	animate_particles(g);
	curr_time = current_time_ms();
	if (f->state == FLY && curr_time - time_log > 5)
	{
		add_particle(g, f);
		f->position.x += cos(f->direction) * 0.05;
		f->position.y += sin(f->direction) * 0.05;
		
		if (fireball_collision(&f->position, g))
		{
			fireball_explode(g, &f->position);
			f->state = IDLE;
			f->position = (t_vector){-1, -1};
		}
		time_log = curr_time;
	}
}
