/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fireball.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 22:32:13 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 20:45:43 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIREBALL_H
# define FIREBALL_H

# include "../../main/vector.h"
# include <stdbool.h>

# define NUM_OF_FIREBALLS 5
# define FIREBALL_DAMAGE 35
# define FIREBALL_BURN_DAMAGE 3
# define FIREBALL_WIDTH 0.2
# define NUM_OF_PARTICLES 25

typedef struct s_fireball			t_fireball;
typedef struct s_fireball_particle	t_fire_particle;
typedef enum e_fireball_state		t_fireball_state;

enum e_fireball_state
{
	F_IDLE = 0,
	F_FLY
};

struct	s_fireball
{
	t_fireball_state	state;
	t_vector			position;
	double				direction;
	t_segment			segment;
	long long			last_update_time;
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
void	animate_particle_y(t_fire_particle *particle);

#endif
