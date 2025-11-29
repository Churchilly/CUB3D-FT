/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 23:01:56 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/29 20:47:51 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ORB_H
# define ORB_H

# include "../../main/vector.h"

# define ORB_RADIUS 0.3
# define ORB_WIDTH 0.1

typedef struct s_main	t_main;

typedef struct s_orb	t_orb;

struct					s_orb
{
	t_vector			position;
	t_segment			segment;
	long long			last_hit_time;
};

void		create_orbs(t_main *g);
int			animate_orb_rotation(void);
void		orb_damage(t_main *g, t_orb *orb);
t_vector	orb_position(t_player *player,
				int start_deg, int curr_orb, int gap);

#endif