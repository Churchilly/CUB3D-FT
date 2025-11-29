/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:41:29 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 20:16:12 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "../main/vector.h"

typedef struct s_player		t_player;
typedef struct s_view		t_view;
typedef struct s_inventory	t_inventory;

typedef struct s_main		t_main;

# define FOV 60.0
# define P_MOVESPEED 0.35
# define P_MOVEMULT 0.05
# define SENSITIVITY 0.4
# define PLAYER_RADIUS 0.1
# define DEFAULT_HEALING 0.05
# define POTION_HEALING 10
# define SPAWN_HEALING 20

# define IMMORTALITY 0

struct s_inventory
{
	int	currency;
	int	adrenaline_potions;
	int	damage_increase;
	int	health_increase;
	int	mana_increase;
	int	cooldown_decreaser;
	int	orb;
};

struct s_player
{
	t_vector	pos;
	double		dov;
	double		mana;
	double		health;
	double		healing;
	t_inventory	inventory;
};

void		change_direction(t_main *g);
void		change_position(t_main *g);
void		change_direction_advanced(t_main *g, int direction, int weight);

t_vector	check_collision(t_main *g, t_vector movement);

void		update_mana(t_main *g);
void		use_mana(t_main *g, double val);
void		update_health(t_main *g);
void		damage_player(t_main *g, double val);

#endif
