/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:23:43 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/24 09:13:18 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "../minilibx/mlx.h"
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
	if (!game->window.mlx)
	{
		printf("Error: Failed to initialize MLX\n");
		exit(1);
	}
	
	// initialize menu-related things (needed before game starts)
	cub_map(&(game->map));
	create_objects_static(game);
	cub_spellbook(&game->spellbook, game->window.mlx); // same as objects need reset
	list_create(&game->rays, WIN_WIDTH * SENSITIVITY * 0.05); // same as obj no need to reset
	init_gallery_with_config(&(game->gallery), NULL);
	init_fonts(game);  // Initialize fonts BEFORE menus that use them
	init_main_menu(game, &(game->main_menu));
	init_map_select_menu(game, &(game->map_select));
	init_error_menu(game, &(game->error_menu));
	init_shop_menu(game, &(game->shop_menu));
	init_game_summary_menu(game, &(game->summary_menu));
	_init_keys(game);

	// Initialize game statistics (total run across all maps)
	game->map.player.inventory.orb = 8;
	game->record.play_time = 0;
	game->record.kill_count = 0;
	game->record.fireballs_cast = 0;
	game->record.total_income = 0;
	game->record.purchase_count = 0;
}


void _init_hooks(t_main *game)
{
	mlx_hook(game->window.win, 2, 1L << 0, onpress_event, game);
	mlx_hook(game->window.win, 3, 1L << 1, onrelease_event, game);
	mlx_hook(game->window.win, 17, 0, terminate_hook, NULL);
	mlx_mouse_hook(game->window.win, mouse_click, game);
	mlx_loop_hook(game->window.mlx, loop_event, game);
}
