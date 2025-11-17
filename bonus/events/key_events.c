/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:29:09 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/17 16:37:53 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include <X11/keysym.h>

#include <stdio.h> // for debug

// 	switch keys are for player to be not able to spam some events by just
// continuously pressing on the key. switch key attribute provide a safe
// switching between active and inactive

static int	onpress_switch_key_menu(t_switch_key *switch_key, int key, t_main *game)
{
	if (!switch_key->key_switch)
	{
		if (key == XK_space)
			activate_button(game);
		if (key == XK_w)
			prev_button(game);
		if (key == XK_s)
			next_button(game);
	}
	return (1);
}
static void onpress_switch_key(t_switch_key *switch_key, int key, t_main *game)
{
	switch_key->key = true;
	if (key == XK_F3)
	{
		printf("im pressin f3 mf\n");
		switch_key->key_switch = !(switch_key->key_switch);
		if (switch_key->key_switch)
			mlx_mouse_hide(game->window.mlx, game->window.win);
		else
			mlx_mouse_show(game->window.mlx, game->window.win);
	}
	else if (!switch_key->key_switch)
	{
		printf("im doing a press event!\n"); // event that will happen when pressed
		if (key == XK_e)
			next_spell(game);
		else if (key == XK_q)
			prev_spell(game);
		else if (key == XK_space)
			cast_spell(game);
		switch_key->key_switch = true;
	}
}

static void onrelease_switch_key(t_switch_key *switch_key)
{
	switch_key->key = false;
}

void unlock_switch(t_main *game)
{
	if (game->key_list.e.key == false)
		game->key_list.e.key_switch = false;
	if (game->key_list.q.key == false)
		game->key_list.q.key_switch = false;
	if (game->key_list.spc.key == false)
		game->key_list.spc.key_switch = false;
}
static void	onpress_event_menu(int key, t_main *game)
{
	if (key == XK_w)
		onpress_switch_key_menu(&(game->key_list.w), key, game);
	else if (key == XK_s)
		onpress_switch_key_menu(&(game->key_list.s), key, game);
	else if (key == XK_space)
		onpress_switch_key_menu(&(game->key_list.spc), key, game);
}
static void	onpress_event_game(int key, t_main *game)
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
}

int onpress_event(int key, t_main *game)
{
	if (game->state == GAME)
		onpress_event_game(key, game);
	else
		onpress_event_menu(key, game);
	return (0);
}

int onrelease_event(int key, t_main *game)
{
	if (key == XK_Escape && game->state != MENU_MAIN)
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
	else if (key == XK_e)
		onrelease_switch_key(&(game->key_list.e));
	else if (key == XK_q)
		onrelease_switch_key(&(game->key_list.q));
	else if (key == XK_space)
		onrelease_switch_key(&(game->key_list.spc));
	// I dont need f3's onrelease event, its gonna be a switch fr
	return (0);
}
