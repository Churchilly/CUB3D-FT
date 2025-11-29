/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:41:45 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 21:50:29 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <math.h>

void	cub_render(t_main *g, t_raycasting_func raycast)
{
	if (raycast == raycasting && check_off_map(g))
		render_black_screen(&g->window);
	else
	{
		render_background(g);
		raycast(g);
		render_scene(g);
	}
	mlx_put_image_to_window(g->window.mlx, g->window.win, g->window.img, 0, 0);
}
