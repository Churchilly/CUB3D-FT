/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_enemy.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 23:36:20 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/19 03:20:34 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_ENEMY_H
# define BONUS_ENEMY_H

# include "../main/vector.h"

# define NUM_OF_ENEMIES 5
# define ENEMY_SPAWN_FREEZE 300
# define ENEMY_SPAWN_PRECISION 4
# define ENEMY_SPAWN_RATE 50
# define ENEMY_SPAWN_DELAY 300
# define ENEMY_SPAWN_DIST 1
# define ENEMY_MOVE_SPEED 0.25
# define ENEMY_MOVE_MULT 0.05
# define ENEMY_RADIUS 0.2
# define ENEMY_HEALTH 100
# define ENEMY_WIDTH 0.5



typedef struct s_enemy		t_enemy;
typedef enum e_enemy_state	t_enemy_state;

enum e_enemy_state
{
	IDLE,
	ALIVE,
	BURNING,
	DYING
};

struct s_enemy
{
	t_vector		position;
	t_segment 		segment;
	int				health;
	int				state;
};

// Forward declarations
typedef struct s_map	t_map;

// Function declarations
void	spawn_enemy(t_enemy *enemy, t_map *map);
void	enemy_walk(t_enemy *enemy, t_map *map);
void	enemy_health(t_enemy *enemy);

#endif