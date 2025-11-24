/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_animate_sprites.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:12:10 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/24 05:11:58 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

void animate_fireball_sprite(t_main *g)
{
	static long long time_log = 0;
	long long curr_time;
	t_cub3_gallery *gal;
	t_im swap;
	
	curr_time = current_time_ms();
	gal = &g->gallery;
	if (curr_time - time_log > 200)
	{
		swap = gal->fireball;
		gal->fireball = gal->fireball2;
		gal->fireball2 = gal->fireball3;
		gal->fireball3 = gal->fireball4;
		gal->fireball4 = swap;
		time_log = curr_time;
	}
}

void animate_fireball_particle_sprite(t_main *g)
{
	static long long time_log = 0;
	long long curr_time;
	t_cub3_gallery *gal;
	t_im swap;
	
	curr_time = current_time_ms();
	gal = &g->gallery;
	if (curr_time - time_log > 220)
	{
		swap = gal->fireball_particle_1;
		gal->fireball_particle_1 = gal->fireball_particle_2;
		gal->fireball_particle_2 = gal->fireball_particle_3;
		gal->fireball_particle_3 = swap;
	}
}
