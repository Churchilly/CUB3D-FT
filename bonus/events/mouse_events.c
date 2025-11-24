/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:50:30 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/24 09:42:51 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include "../minilibx/mlx_int.h"
#include <X11/Xlib.h>

void	center_mouse(t_main *game)
{
	t_xvar	*xvar;
	Display	*display;
	Window	window_cub3d;

	xvar = (t_xvar *)game->window.mlx;
	display = xvar->display;
	window_cub3d = xvar->win_list->window;
	XWarpPointer(display, None, window_cub3d,
		0, 0, 0, 0,
		WIN_WIDTH / 2, WIN_HEIGHT / 2);
}

t_vector	get_mouse_position(t_main *game)
{
	t_xvar			*xvar;
	Window			cub3d;
	t_vector_int	win;
	unsigned int	m;
	t_vector		response;

	xvar = (t_xvar *)game->window.mlx;
	cub3d = xvar->win_list->window;
	XQueryPointer(xvar->display, cub3d,
		&cub3d, &cub3d, &win.x, &win.x, &win.x, &win.y, &m);
	response.x = win.x;
	response.y = win.y;
	return (response);
}

void	read_mouse_movements(t_main *game)
{
	t_xvar			*xvar;
	Window			cub3d;
	t_vector_int	win;
	unsigned int	m;
	int				win_x_abs;

	xvar = (t_xvar *)game->window.mlx;
	cub3d = xvar->win_list->window;
	XQueryPointer(xvar->display, cub3d,
		&cub3d, &cub3d, &win.x, &win.x, &win.x, &win.y, &m);
	win_x_abs = win.x - WIN_WIDTH / 2;
	if (win_x_abs > 0)
		change_direction_advanced(game, 'R', win_x_abs);
	else if (win_x_abs < 0)
		change_direction_advanced(game, 'L', win_x_abs);
}

int	mouse_click(int button, int x, int y, void *game)
{
	t_main	*g;

	(void)button;
	g = (t_main *)game;
	if (g->state == MENU_MAIN || g->state == MENU_PAUSE)
		mouse_click_main_pause(x, y, game);
	else if (g->state == MENU_MAP_SELECT)
		mouse_click_map_select(x, y, game);
	else if (g->state == MENU_SHOP)
		mouse_click_shop(x, y, game);
	else if (g->state == MENU_ERROR || g->state == MENU_SUMMARY)
		g->state = MENU_MAIN;
	return (0);
}
