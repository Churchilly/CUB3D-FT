/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fireball_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 05:24:14 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 20:44:55 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

void	create_fireballs(t_main *g)
{
	int			counter;
	t_fireball	*fireball;

	counter = NUM_OF_FIREBALLS;
	while (counter--)
	{
		fireball = alloc(sizeof(t_fireball), STATIC);
		fireball->direction = 0.0;
		fireball->position.x = -1.0;
		fireball->position.y = -1.0;
		fireball->last_update_time = 0;
		fireball->state = F_IDLE;
		add_object(&g->objects, FIREBALL, fireball, STATIC);
	}
}

void	create_particles(t_main *g)
{
	int				counter;
	t_fire_particle	*particle;

	counter = NUM_OF_PARTICLES;
	while (counter--)
	{
		particle = alloc(sizeof(t_fire_particle), STATIC);
		particle->active = false;
		particle->position.x = -1.0;
		particle->position.y = -1.0;
		add_object(&g->objects, PARTICLE, particle, STATIC);
	}
}
