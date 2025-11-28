/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_door.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 03:26:34 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 03:33:34 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_DOORS_H
# define BONUS_DOORS_H

// Forward declarations
typedef struct s_main		t_main;
typedef struct s_door_wall	t_door_wall;

# include "../../main/vector.h"

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
	D_OPEN = 11, // blue, alpha 0.4, no collision
	D_CLOSE, // locked (red, alpha 0.8, has collision)
	D_LOCKING, // animation: OPEN -> CLOSE
	D_UNLOCKING // animation: CLOSE -> OPEN
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


t_door_wall	*find_door_wall(int x, int y, t_door_wall *door_walls);
t_door		*find_interactable_door(t_main *g);
void		create_barriers(t_main *g);
void	animate_door(t_door *door);

#endif
