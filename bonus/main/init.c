/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:23:43 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/12 20:35:36 by btuncer          ###   ########.fr       */
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

static void	_init_texture(t_texture *src, char *dst, void *mlx)
{
	src->img = mlx_xpm_file_to_image(mlx, dst, &src->width, &src->height);
	if (!src->img)
	{
		printf("Error: Failed to load texture %s\n", dst);
		exit(1);
	}
	src->addr = mlx_get_data_addr(src->img,
		&src->bits_per_pixel, &src->line_length,
		&src->endian);
}

static void	_init_spellbook(t_spellbook *spellbook, void *mlx)
{
	int	target_width;
	int	scaled_width;
	int	scaled_height;

	_init_texture(&spellbook->texture_fireball, "textures/fireball_spellbook.xpm", mlx);
	_init_texture(&spellbook->texture_lock, "textures/lock_spellbook.xpm", mlx);
	_init_texture(&spellbook->texture_unlock, "textures/unlock_spellbook.xpm", mlx);
	spellbook->current = FIRBALL;
	spellbook->cur_texture = &spellbook->texture_fireball;
	spellbook->cooldown = 0;
	spellbook->changing_direction = 0;
	target_width = (int)(WIN_WIDTH * SPELLBOOK_TARGET_WIDTH_RATIO);
	spellbook->scale = (float)SPELLBOOK_WIDTH / (float)target_width;
	scaled_width = (int)(SPELLBOOK_WIDTH / spellbook->scale);
	scaled_height = (int)(SPELLBOOK_HEIGHT / spellbook->scale);
	spellbook->win_pos.x = (WIN_WIDTH - scaled_width) / 2;
	spellbook->win_pos.y = WIN_HEIGHT - scaled_height + (WIN_HEIGHT / 10);
	spellbook->original_win_pos.x = spellbook->win_pos.x;
	spellbook->original_win_pos.y = spellbook->win_pos.y;
}

void	__init__(t_main *game)
{
	memset(game, 0, sizeof(t_main));
	game->window.mlx = mlx_init(); // connection to mlx for textures
	safe_mlx(game->window.mlx, op_mlx); // insert connection into the safe
	if (!game->window.mlx)
	{
		printf("Error: Failed to initialize MLX\n");
		exit(1);
	}
	game->map.player.pos.x = -1;
	game->map.player.pos.y = -1;
	game->map.player.mana = MAX_MANA;
	game->map.player.health = MAX_HEALTH;
	init_gallery_with_config(&(game->gallery), NULL); // config will be here. // no hud inits before gallery
	init_main_menu(game, &(game->main_menu));
	_init_keys(game);
	list_create(&game->rays, WIN_WIDTH * SENSITIVITY * 0.05);
	_init_spellbook(&game->spellbook, game->window.mlx);
}

void _init_hooks(t_main *game)
{
	mlx_hook(game->window.win, 2, 1L << 0, onpress_event, game);
	mlx_hook(game->window.win, 3, 1L << 1, onrelease_event, game);
	mlx_hook(game->window.win, 17, 0, terminate_hook, NULL);
	mlx_mouse_hook(game->window.win, mouse_click, game);
	mlx_loop_hook(game->window.mlx, loop_event, game);
}
