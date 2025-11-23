/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_animate_orbs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 23:10:30 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/24 00:22:17 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <math.h>

static t_vector orb_position(t_player *player, int start_deg, int curr_orb, int gap)
{
	t_vector pos;
	double angle_deg;
	double angle_rad;

	angle_deg = start_deg + (curr_orb * gap);
	angle_rad = angle_deg * M_PI / 180.0;
	pos.x = player->pos.x + cos(angle_rad) * ORB_RADIUS;
	pos.y = player->pos.y + sin(angle_rad) * ORB_RADIUS;
	return (pos);
}

static int animate_orb_rotation(void)
{
    static int start_deg = 0;
    static long long time_log;
    long long curr_time;

    curr_time = current_time_ms();
    if (curr_time - time_log > 30)
    {
        if (start_deg == 359)
            start_deg = 0;
        else
            start_deg++;
        time_log = curr_time;
    }
    return (start_deg);
}

static void orb_damage(t_main *g, t_orb *orb)
{
    long long curr_time;
    t_obj_node *obj;
    t_enemy *enemy;
    t_vector dist;
    double distance;

    curr_time = current_time_ms();
    if (curr_time - orb->last_hit_time < 300)
        return ;
    obj = g->objects.all;
    while (obj)
    {
        if (obj->type == ENEMY && ((t_enemy *)obj->object)->state == ALIVE)
        {
            enemy = (t_enemy *)obj->object;
            dist.x = orb->position.x - enemy->position.x;
            dist.y = orb->position.y - enemy->position.y;
            distance = sqrt(dist.x * dist.x + dist.y * dist.y);
            if (distance < 0.2)
            {
                damage_enemy(enemy, 1, g);
                orb->last_hit_time = curr_time;
                return ;
            }
        }
        obj = obj->next;
    }
}

static void place_orbs(t_main *g, int start_deg)
{
    t_obj_node *obj;
    t_orb *orb;
    int curr_orb;
    int gap;
    
    curr_orb = 0;
    gap = 360 / 72; // number of orbs
    obj = g->objects.all;
    while (obj)
    {
        if (obj->type == ORB)
        {
            orb = obj->object;
            orb->position = orb_position(&g->map.player, start_deg, curr_orb, gap);
            orb_damage(g, orb);
            curr_orb++;
        }
        obj = obj->next;
    }
}

void animate_orbs(t_main *g)
{
    int start_deg;

    start_deg = animate_orb_rotation();
    place_orbs(g, start_deg);
}
