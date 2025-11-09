/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_enemy.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 23:36:20 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/09 02:20:47 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_ENEMY_H
# define BONUS_ENEMY_H

# include "../main/vector.h"

# define NUM_OF_ENEMIES 5
# define SPAWN_RATE 4
# define ENEMY_SPEED 1
# define ENEMY_RADIUS 0.2
# define ENEMY_HEALTH 100


typedef struct s_enemy		t_enemy;
typedef enum e_enemy_state	t_enemy_state;

enum e_enemy_state
{
	IDLE,
	ALIVE,
	BURNING
};

struct s_enemy
{
	t_vector		position;
	int				health;
	int				state;
};


#endif