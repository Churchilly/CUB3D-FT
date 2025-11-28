/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 10:25:35 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 22:21:28 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <math.h>

void	render_scene(t_main *g)
{
	t_ray_node	*current;
	int			i;
	int			j;

	current = g->rays.head;
	i = -1;
	while (current && ++i < g->rays.list_size)
	{
		j = -1;
		while (++j < g->rays.package_size)
		{
			draw_floor_column(g, j + (i * g->rays.package_size),
				&(current->ray_pack[j]));
			draw_wall_column(g, j + (i * g->rays.package_size),
				&(current->ray_pack[j]));
		}
		current = current->next;
	}
}
