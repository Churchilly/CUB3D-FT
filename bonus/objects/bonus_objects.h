/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_objects.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 02:13:10 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 20:34:25 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_OBJECTS_H
# define BONUS_OBJECTS_H

// Forward declarations
typedef struct s_main			t_main;
typedef struct s_player			t_player;
typedef struct s_vector			t_vector;

# include "fireball/bonus_fireball.h"
# include "door/bonus_door.h"
# include "enemy/bonus_enemy.h"
# include "orb/bonus_orb.h"

typedef struct s_object_node	t_obj_node;
typedef struct s_object_list	t_obj_list;
typedef enum e_object_types		t_obj_type;
typedef struct s_fov_data		t_fov_data;

# define INFINITY_DISTANCE 1e30

enum e_object_types
{
	DOOR,
	FIREBALL,
	PARTICLE,
	ENEMY,
	ENEMY_PARTICLE,
	ORB
};

struct s_object_node
{
	int		type;
	void	*object;
	t_obj_node	*next;
	// for render
	double		distance;
	t_obj_node	*next_render;
};

struct s_object_list
{
	t_obj_node *o_static;
	t_obj_node *o_dynamic;
	t_obj_node *to_render;
};


void	create_objects_static(t_main *g);
void	create_objects_dynamic(t_main *g);
void	add_object(t_obj_list *list, int type, void *obj, t_section sec);
void	add_to_render_queue(t_obj_list *list, t_obj_node *object, t_player *player);
void	clear_render_queue(t_obj_list *list);
// in process
void	animate_objects(t_main *g);

#endif
