/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 03:26:34 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/21 04:39:48 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOORS_H
# define DOORS_H

# include "../main/vector.h"


# define DOOR_WIDTH 0.4

# define DOOR_ALPHA_OPEN 0.4
# define DOOR_ALPHA_LOCKED 0.7

# define DOOR_COLOR_OPEN 0x0000FF
# define DOOR_COLOR_LOCKED 0xFF0000

# define DOOR_INTERACT_DISTANCE 2.0
# define DOOR_LOCK_ANIMATION_SPEED 0.01

typedef struct s_door_wall	t_door_wall;
typedef struct s_door		t_door;

enum e_door_states
{
	OPEN = 11, // blue, alpha 0.4, no collision
	CLOSE, // locked (red, alpha 0.8, has collision)
	LOCKING, // animation: OPEN -> CLOSE
	UNLOCKING // animation: CLOSE -> OPEN
};

struct s_door_wall
{
	t_vector_int	map_pos;
	t_segment		inner_wall_1; // the wall inside the wall
	t_segment		inner_wall_2;
	int				axis; // 0 -> horizontal [d on map], 1 -> vertical [D on map]
};

struct s_door
{
	int			state;
	t_segment	barrier;
	int			color;
	double		alpha;
};

typedef struct s_main	t_main;

t_door_wall	*find_door_wall(int x, int y, t_door_wall *new);
t_door		*find_interactable_door(t_main *g);
void		create_barriers(t_main *g);
/*
door on map
111111
100001
111611
1000N1
111111

on render


*/

#endif