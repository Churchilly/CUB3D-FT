/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_enemy.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 23:36:20 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 03:27:03 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_ENEMY_H
# define BONUS_ENEMY_H

# include "../../main/vector.h"

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
# define ENEMY_DAMAGE 7
# define ENEMY_EFFECT_RADIUS 80
# define ENEMY_EFFECT_START_OFFSET 10
# define ENEMY_EFFECT_COLOR 0xFF0000
# define ENEMY_ANIMATION_DELAY 5

typedef struct s_enemy		t_enemy;
typedef struct s_enemy_particle t_enemy_particle;
typedef enum e_enemy_state	t_enemy_state;

enum e_enemy_state
{
	E_IDLE,
	E_ALIVE,
	E_ATTACKING,
	E_DYING
};

struct s_enemy
{
	t_vector		position;
	t_segment 		segment;
	int				health;
	int				state;
	double			red_alpha;
	long long attack_time_log;
	t_text dying_effect;
	int effect_phase;
};

struct s_enemy_particle
{
	t_vector position;
	t_segment segment;
};

// Forward declarations
typedef struct s_map	t_map;

// Function declarations
void	spawn_enemy(t_enemy *enemy, t_map *map);
void	enemy_walk(t_enemy *enemy, t_main *g);
void	damage_enemy(t_enemy *enemy, double damage, t_main *g);
void	draw_enemy_effect(t_enemy *enemy, t_player *player, t_window *win);
void	enemy_attack(t_enemy *enemy, t_main *g);
void	animate_enemy(t_enemy *enemy, t_main *g);
void animate_enemy_effect(t_enemy *enemy);
void	create_enemies(t_main *g);

#endif