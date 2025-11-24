/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_orb_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 05:28:04 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/24 05:28:26 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

void create_orbs(t_main *g)
{
	int orb_count = 72; // gather this from g->player.inventory.orb
	t_orb *orb;
	
	while (orb_count--)
	{
		orb = alloc(sizeof(t_orb), DYNAMIC);
		orb->position = (t_vector){-1, -1};
		orb->last_hit_time = 0;
		add_object(&g->objects, ORB, orb);
	}
}