/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 19:22:07 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/21 03:33:04 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <stddef.h>

void	add_object(t_obj_list *list, int type, void *obj);

static void	create_enemies(t_main *g)
{
	int	i;
	t_enemy *enemy;

	i = -1;
	while (++i < NUM_OF_FIREBALLS)
	{
		enemy = alloc(sizeof(t_fireball), STATIC);
		enemy->health = ENEMY_HEALTH;
		enemy->state = IDLE;
		enemy->position.x = -1.0;
		enemy->position.y = -1.0;
		enemy->red_alpha = 0.0;
		add_object(&g->objects, ENEMY, enemy);
	}
}

static void	create_fireballs(t_main *g)
{
	int	counter;
	t_fireball *fireball;

	counter = NUM_OF_FIREBALLS;
	while (counter--)
	{
		fireball = alloc(sizeof(t_fireball), STATIC);
		fireball->direction = 0.0;
		fireball->position.x = -1.0;
		fireball->position.y = -1.0;
		fireball->state = F_IDLE;
		add_object(&g->objects, FIREBALL, fireball);
	}
}

static void create_particles(t_main *g)
{
	int counter;
	t_fire_particle *particle;

	counter = NUM_OF_PARTICLES;
	while (counter--)
	{
		particle = alloc(sizeof(t_fire_particle), STATIC);
		particle->active = false;
		particle->position.x = -1.0;
		particle->position.y = -1.0;
		add_object(&g->objects, PARTICLE, particle);
	}
}



static void create_orbs(t_main *g)
{
	int orb_count = 4; // gather this from g->player.inventory.orb
	t_orb *orb;
	
	while (orb_count--)
	{
		orb = malloc(sizeof(t_orb));
		orb->position = (t_vector){-1, -1};
		orb->last_hit_time = 0;
		add_object(&g->objects, ORB, orb);
	}
}

#include <stdio.h>

static void debug(t_main *g)
{
    t_obj_node *curr = g->objects.all;
    int fireball_count = 0;
    int door_count = 0;
    int enemy_count = 0;
    
    printf("=== OBJECT LIST DEBUG ===\n");
    
    while (curr)
    {
        if (curr->type == FIREBALL)
        {
            t_fireball *fb = (t_fireball *)curr->object;
            printf("FIREBALL #%d:\n", fireball_count++);
            printf("  Position: (%.2f, %.2f)\n", fb->position.x, fb->position.y);
            printf("  Direction: %.2f radians\n", fb->direction);
            printf("  Status: %s\n", (fb->position.x < 0) ? "INACTIVE" : "ACTIVE");
            printf("\n");
        }
        else if (curr->type == DOOR)
        {
            t_door *door = (t_door *)curr->object;
            printf("DOOR #%d:\n", door_count++);
            printf("  State: %d\n", door->state);
            printf("  Barrier 1:\n");
            printf("    Start: (%.2f, %.2f)\n", door->barrier.s.x, door->barrier.s.y);
            printf("    End:   (%.2f, %.2f)\n", door->barrier.e.x, door->barrier.e.y);
            printf("\n");
        }
        else if (curr->type == ENEMY)
        {
            t_enemy *enemy = (t_enemy *)curr->object;
            printf("ENEMY #%d:\n", enemy_count++);
            printf("  Position: (%.2f, %.2f)\n", enemy->position.x, enemy->position.y);
            printf("  Health: %d\n", enemy->health);
            printf("  State: %d (%s)\n", enemy->state, 
                   enemy->state == IDLE ? "IDLE" : enemy->state == ALIVE ? "ALIVE" : 
                   enemy->state == BURNING ? "BURNING" : "UNKNOWN");
            printf("  Status: %s\n", (enemy->position.x < 0) ? "INACTIVE" : "ACTIVE");
            printf("\n");
        }
        else
        {
            printf("UNKNOWN OBJECT TYPE: %d\n", curr->type);
        }
        curr = curr->next;
    }
    
    printf("=== SUMMARY ===\n");
    printf("Total Fireballs: %d\n", fireball_count);
    printf("Total Doors: %d\n", door_count);
    printf("Total Enemies: %d\n", enemy_count);
    printf("Total Objects: %d\n", fireball_count + door_count + enemy_count);
    printf("==================\n\n");
}

void	cub_objects(t_main *g)
{
	create_fireballs(g);
	create_particles(g);
	create_enemies(g);
	// this shit need to go to map creation !remember
	//
	create_orbs(g);
	debug(g);
}