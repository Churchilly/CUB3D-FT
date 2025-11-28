/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:29:09 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/28 21:21:35 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	delayed_event(t_main *g, t_game_state state)
{
	static long long	time_log = 0;
	long long			curr_time;

	curr_time = current_time_ms();
	if (time_log == 0)
	{
		time_log = curr_time;
		return ;
	}
	if (curr_time - time_log < 3000)
		return ;
	time_log = 0;
	g->state = state;
}

int	onpress_event(int key, t_main *game)
{
	if (game->state == GAME)
		onpress_event_game(key, game);
	else if (game->state == MENU_ERROR || game->state == MENU_SUMMARY)
		delayed_event(game, MENU_MAIN);
	else
		onpress_event_menu(key, game);
	return (0);
}
