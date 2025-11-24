/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_orb.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 23:01:56 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/24 07:53:57 by btuncer          ###   ########.fr       */
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
void create_orbs(t_main *g);
int animate_orb_rotation(void);
void orb_damage(t_main *g, t_orb *orb);
t_vector orb_position(t_player *player, int start_deg, int curr_orb, int gap);

#endif