/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:33:18 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/16 02:56:22 by btuncer          ###   ########.fr       */
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

static int loop_main_menu(t_main *game)
{
	cub_render(game);
	// check_button;
	return (0);	
}

static int loop_game(t_main *game)
{
	cub_render(game);
	change_position(game, 0);
	change_direction(game, 0);
	
	update_mana(game);
	update_health(game);
	
	if (game->key_list.f3.key_switch)
	{
		read_mouse_movements(game);
		center_mouse(game);
	}
	
	unlock_switch(game);
	return (0);	
}

int loop_event(t_main *game)
{
	static long long time_log = 0;
	long long curr_time;

	curr_time = current_time_ms();
	if (!(curr_time - time_log > 16))
		return (0);
	time_log = curr_time;
	if (game->main_menu.active)
		return (loop_main_menu(game));
	else
		return (loop_game(game));
}
