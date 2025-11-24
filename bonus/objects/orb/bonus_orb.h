/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_orb.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 23:01:56 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/24 05:28:42 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_ORB_H
# define BONUS_ORB_H

# define ORB_RADIUS 0.3
# define ORB_WIDTH 0.1

typedef struct s_main			t_main;

# include "../../main/vector.h"

typedef struct s_orb t_orb;

struct s_orb
{
	// idx 0 -> 0 1 -> 120 2 -> 240
    t_vector position;
    t_segment segment;
    long long last_hit_time;
};

// player
void animate_orbs(t_main *g);
void create_orbs(t_main *g);

#endif