/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_orb_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 05:28:04 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/24 10:25:44 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

void create_orbs(t_main *g)
{
	int orb_count;
	t_orb *orb;
	
	orb_count = g->map.player.inventory.orb;
	while (orb_count--)
	{
		orb = alloc(sizeof(t_orb), DYNAMIC);
		orb->position = (t_vector){-1, -1};
		orb->last_hit_time = 0;
		add_object(&g->objects, ORB, orb, DYNAMIC);
	}
}
