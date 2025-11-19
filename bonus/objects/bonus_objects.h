/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_objects.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 02:13:10 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/20 00:51:12 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS
# define OBJECTS

// Forward declarations
typedef struct s_main			t_main;
typedef struct s_player			t_player;
typedef struct s_cub3_gallery	t_cub3_gallery;
typedef struct s_fireball		t_fireball;
typedef struct s_vector			t_vector;

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
	t_obj_node *all;
	t_obj_node *to_render;
};


void	cub_objects(t_main *g);
void	add_object(t_obj_list *list, int type, void *obj);
void	add_to_render_queue(t_obj_list *list, t_obj_node *object, t_player *player);
void	clear_render_queue(t_obj_list *list);
void	create_render_queue(t_main *g);
// in process
void	animate_objects(t_main *g);

// sprite animations
void animate_fireball_sprite(t_main *g);
void animate_fireball_particle_sprite(t_main *g);

// fireball and particle animations
void	animate_fireball(t_fireball *f, t_main *g, t_cub3_gallery *gal);
void fireball_explode(t_main *g, t_vector *f_pos);

#endif