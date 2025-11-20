/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:23:43 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/20 17:59:18 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "../minilibx/mlx.h"
#include "../gc/gc.h"
#include "../player/player.h"
#include "../events/events.h"
#include <X11/Xlib.h>
#include "../minilibx/mlx_int.h"

void center_window(t_main *g)
{
	t_xvar *xvar;
	Display *display;
	Window window;
	Screen *screen;
	
	xvar = (t_xvar *)g->window.mlx;
	display = xvar->display;
	window = xvar->win_list->window;
	screen = DefaultScreenOfDisplay(display);
	XMoveWindow(display, window, screen->width / 2 - WIN_WIDTH / 2,
											screen->height / 2 - WIN_HEIGHT / 2 - WIN_HEIGHT / 5);	
	XFlush(xvar->display);
}

static void _init_keys(t_main *game)
{
	game->key_list.w = false;
	game->key_list.a = false;
	game->key_list.s = false;
	game->key_list.d = false;
	game->key_list.arrow_l = false;
	game->key_list.arrow_r = false;
	
	// switch keys
	game->key_list.e.key = false;
	game->key_list.e.key_switch = false;
	game->key_list.q.key = false;
	game->key_list.q.key_switch = false;
	game->key_list.spc.key = false;
	game->key_list.spc.key_switch = false;
	game->key_list.f3.key = false;
	game->key_list.f3.key_switch = false;
}

void	__init__(t_main *game)
{
	memset(game, 0, sizeof(t_main));
	
	// Initialize MLX connection
	game->window.mlx = mlx_init();
	safe_mlx(game->window.mlx, op_mlx);
	if (!game->window.mlx)
	{
		printf("Error: Failed to initialize MLX\n");
		exit(1);
	}
	
	// Initialize menu-related things (needed before game starts)
	cub_map(&(game->map));
	init_gallery_with_config(&(game->gallery), NULL);
	init_fonts(game);  // Initialize fonts BEFORE menus that use them
	init_main_menu(game, &(game->main_menu));
	init_map_select_menu(game, &(game->map_select));
	init_error_menu(game, &(game->error_menu));
	_init_keys(game);
}


void _init_hooks(t_main *game)
{
	mlx_hook(game->window.win, 2, 1L << 0, onpress_event, game);
	mlx_hook(game->window.win, 3, 1L << 1, onrelease_event, game);
	mlx_hook(game->window.win, 17, 0, terminate_hook, NULL);
	mlx_mouse_hook(game->window.win, mouse_click, game);
	mlx_loop_hook(game->window.mlx, loop_event, game);
}
