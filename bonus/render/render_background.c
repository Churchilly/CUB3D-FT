/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:15:12 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/22 05:22:12 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	render_background(t_main *g)
{
	int	x;
	int	y;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			if (y < (WIN_HEIGHT / 2))
				put_pixel(x, y, g->map.color_c, &g->window);
			// Floor is now rendered as texture in render_scene.c
			// Removed: else put_pixel(x, y, g->map.color_f, &g->window);
		}
	}
}
