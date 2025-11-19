/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_orbs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 23:01:56 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/20 02:04:02 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_ORBS_H
# define BONUS_ORBS_H

# define ORB_RADIUS 0.3
# define ORB_WIDTH 0.1

# include "../main/vector.h"

typedef struct s_orb t_orb;

struct s_orb
{
    t_vector position;
    t_segment segment;
    long long last_hit_time;
};

void animate_orbs(t_main *g);

#endif