/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:33:18 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/17 16:28:54 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include <stdio.h> // for debug

int terminate_hook(void)
{
	printf("dont kill me :c\n");
	exit(0);
	return (0);
}

static void	update_game(t_main *g)
{
	change_position(g, 0);
	change_direction(g, 0);
	
	update_mana(g);
	update_health(g);
	
	if (g->key_list.f3.key_switch)
	{
		read_mouse_movements(g);
		center_mouse(g);
	}
	unlock_switch(g);
}

static void	fps_counter(long long curr_time)
{
	static int frame_count = 0;
	static long long time_log = 0;

	frame_count++;
	if (curr_time - time_log >= 1000)
	{
		printf("%ifps\n", frame_count);
		frame_count = 0;
		time_log = curr_time;
	}
}

int loop_event(t_main *game)
{
	static long long time_log = 0;
	long long curr_time;

	curr_time = current_time_ms();
	if (!(curr_time - time_log > 16))
		return (0);
	time_log = curr_time;
	fps_counter(curr_time);
	if (game->state == MENU_MAIN)
		render_main_menu(game);
	else if (game->state == MENU_PAUSE)
		render_pause_menu(game);
	else if (game->state == GAME)
	{
		render_game(game);
		update_game(game);
	}
	else if (game->state == MENU_MAP_SELECT)
		return (0);
	else if (game->state == MENU_SHOP)
		return (0);
}
