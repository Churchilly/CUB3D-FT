/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 04:31:29 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 21:44:58 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "../minilibx/mlx.h"

void	cub_create_window(t_main *g)
{
	t_window	*d;

	d = &g->window;
	d->win = mlx_new_window(d->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!d->win)
		exit(1);
	d->img = mlx_new_image(d->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!d->img)
		exit(1);
	d->addr = mlx_get_data_addr(d->img, &(d->bits_per_pixel),
			&(d->line_length), &(d->endian));
}
