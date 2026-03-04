/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 07:18:33 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 21:21:26 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <X11/keysym.h>

static void	onpress_switch_key(t_switch_key *switch_key, int key, t_main *game)
{
	switch_key->key = true;
	if (key == XK_F3)
	{
		switch_key->key_switch = !(switch_key->key_switch);
		if (switch_key->key_switch)
			mlx_mouse_hide(game->window.mlx, game->window.win);
		else
			mlx_mouse_show(game->window.mlx, game->window.win);
	}
	else if (!switch_key->key_switch)
	{
		if (key == XK_e)
			next_spell(game);
		else if (key == XK_q)
			prev_spell(game);
		else if (key == XK_space)
			cast_spell(game);
		switch_key->key_switch = true;
	}
}

void	onpress_event_game(int key, t_main *game)
{
	if (key == XK_w)
		game->key_list.w = true;
	else if (key == XK_a)
		game->key_list.a = true;
	else if (key == XK_s)
		game->key_list.s = true;
	else if (key == XK_d)
		game->key_list.d = true;
	else if (key == XK_Left)
		game->key_list.arrow_l = true;
	else if (key == XK_Right)
		game->key_list.arrow_r = true;
	else if (key == XK_e)
		onpress_switch_key(&(game->key_list.e), key, game);
	else if (key == XK_q)
		onpress_switch_key(&(game->key_list.q), key, game);
	else if (key == XK_space)
		onpress_switch_key(&(game->key_list.spc), key, game);
	else if (key == XK_F3)
		onpress_switch_key(&(game->key_list.f3), key, game);
	else if (key == XK_F9)
		game->map.map_timer *= 1e10;
	else if (key == XK_F10)
		game->map.player.inventory.currency += 5000;
}

void	unlock_switch(t_main *game)
{
	if (game->key_list.e.key == false)
		game->key_list.e.key_switch = false;
	if (game->key_list.q.key == false)
		game->key_list.q.key_switch = false;
	if (game->key_list.spc.key == false)
		game->key_list.spc.key_switch = false;
}

static void	onrelease_switch_key(t_switch_key *switch_key)
{
	switch_key->key = false;
}

int	onrelease_event(int key, t_main *game)
{
	if (key == XK_Escape)
		switch_menu(game);
	else if (key == XK_w)
		game->key_list.w = false;
	else if (key == XK_a)
		game->key_list.a = false;
	else if (key == XK_s)
		game->key_list.s = false;
	else if (key == XK_d)
		game->key_list.d = false;
	else if (key == XK_Left)
		game->key_list.arrow_l = false;
	else if (key == XK_Right)
		game->key_list.arrow_r = false;
	else if (key == XK_space || key == XK_Return)
		onrelease_switch_key(&(game->key_list.spc));
	else if (key == XK_e)
		onrelease_switch_key(&(game->key_list.e));
	else if (key == XK_q)
		onrelease_switch_key(&(game->key_list.q));
	return (0);
}
