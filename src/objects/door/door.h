/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 03:26:34 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 20:42:52 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOR_H
# define DOOR_H

# include "../../main/vector.h"

typedef struct s_main		t_main;
typedef struct s_door_wall	t_door_wall;

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
	D_OPEN = 11,
	D_CLOSE,
	D_LOCKING,
	D_UNLOCKING
};

struct s_door_wall
{
	t_vector_int	map_pos;
	t_segment		inner_wall_1;
	t_segment		inner_wall_2;
	int				axis;
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
void		animate_door(t_door *door);

#endif
