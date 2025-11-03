/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_collisions.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 09:26:46 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/03 09:49:30 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_COLLISIONS_H
# define BONUS_COLLISIONS_H

# include "../main/main.h"

t_vector	check_collision(t_main *g, t_vector movement);

double		find_wall_collision(t_cast_data *d, t_vector pos, char **map,
				double max_dist);
double		find_doorwall_collision(t_cast_data *d, char **map);
double		find_object_collision(t_cast_data *d, t_main *g);

double		calculate_hit_position(t_cast_data *d, t_vector pos, int side);
double		find_collision_distance(t_cast_data *d, t_segment wall);
double		calculate_wall_distance(t_cast_data *d, t_vector pos, int side);

void		init_ray_axis(double delta, double *ray_dir, double *delta_dist);
void		init_y_axis_direction(t_cast_data *d);
void		init_x_axis_direction(t_cast_data *d);

#endif