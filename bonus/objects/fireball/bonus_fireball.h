/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_fireball.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 22:32:13 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/24 07:32:10 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
casting
	when checking need to create a fireball segment according to player->dov
		this segment's length is according to u
		segment's angle is right to player->dov
	also according to player->dov init side data
	use check intersection function to find hit and distance of fireball ray
	after using intersection function check if ray is in player's sight
	if it is insert the index according to direction and player->dov
rendering
	check if current rendering part of screen == index
	if so check the currennt rendering part's ray distance and compare it with fireball_ray->distance
	put the fireball texture after wall
*/

#ifndef BONUS_FIREBALL_H
# define BONUS_FIREBALL_H

# include "../../main/vector.h"
# include <stdbool.h>

# define NUM_OF_FIREBALLS 5
# define FIREBALL_DAMAGE 5
# define FIREBALL_BURN_DAMAGE 3
# define FIREBALL_WIDTH 0.2
# define NUM_OF_PARTICLES 25

typedef struct s_fireball		t_fireball;
typedef struct s_fireball_particle t_fire_particle;
typedef enum e_fireball_state	t_fireball_state;

enum e_fireball_state
{
	F_IDLE = 0,
	FLY,
	BLAST
};

struct	s_fireball
{
	t_fireball_state	state;
	t_vector			position;
	double				direction;
	t_segment			segment;
};

struct s_fireball_particle
{
	t_vector	position;
	t_segment	segment;
	t_im		image;
	int			start_y;
	bool		active;
};

void	create_fireballs(t_main *g);
void	create_particles(t_main *g);

void	fireball_explode(t_main *g, t_vector *f_pos);

void	animate_fireball_sprite(t_main *g);
void	animate_fireball_particle_sprite(t_main *g);

void	animate_fireball(t_fireball *f, t_main *g);
void animate_particle_y(t_fire_particle *particle);

#endif
