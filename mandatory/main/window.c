/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 04:31:29 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 21:46:05 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gc/gc.h"
#include "../minilibx/mlx.h"
#include "main.h"
#include <X11/X.h>
#include <X11/keysym.h>

static int	quit(t_main *g)
{
	mlx_destroy_image(g->window.mlx, g->window.img);
	map_cleanup(g);
	exit(0);
	return (0);
}

static int	keys(int key, t_main *g)
{
	if (key == XK_Escape)
		quit(g);
	if (key == XK_w || key == XK_s || key == XK_a || key == XK_d)
		change_position(g, key);
	if (key == XK_Right || key == XK_Left)
		change_direction(g, key);
	return (0);
}

void	cub_create_window(t_main *g)
{
	t_window	*d;

	d = &g->window;
	d->win = mlx_new_window(d->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!d->win)
		exit(1);
	safe_mlx(d->win, op_win);
	d->img = mlx_new_image(d->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!d->img)
		exit(1);
	d->addr = mlx_get_data_addr(d->img, &(d->bits_per_pixel), &(d->line_length),
			&(d->endian));
	mlx_hook(d->win, ClientMessage, StructureNotifyMask, quit, g);
	mlx_hook(d->win, KeyPress, KeyPressMask, keys, g);
}
