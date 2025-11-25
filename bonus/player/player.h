/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:41:29 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/25 15:35:55 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "../main/vector.h"

typedef struct s_player t_player;
typedef struct s_view	t_view;
typedef struct s_inventory t_inventory;

typedef struct s_main	t_main; // forward dec

# define FOV 60.0
# define PLAYER_MOVE_SPEED 0.35
# define PLAYER_MOVE_MULT 0.05
# define SENSITIVITY 0.4
# define PLAYER_RADIUS 0.1
# define DEFAULT_HEALING 0.1
# define POTION_HEALING 10;

struct s_inventory
{
	int currency;
	int adrenaline_potions;
	int damage_increase;
	int mana_increase;
	int cooldown_decreaser;
	int	orb;
};

struct s_player
{
	t_vector	pos;
	double		dov; // direction of view
	double		mana;
	double		health;
	double 		healing;
	t_inventory inventory;
};

void	change_direction(t_main *g);
void	change_position(t_main *g);
void	change_direction_advanced(t_main *g, int direction, int weight);

t_vector	check_collision(t_main *g, t_vector movement);

void update_mana(t_main *g);
void use_mana(t_main *g, double val);
void update_health(t_main *g);
void damage_player(t_main *g, double val);

#endif

// q, mouse2 -> next spell
// e -> interaction
// spc, mouse1 -> cast