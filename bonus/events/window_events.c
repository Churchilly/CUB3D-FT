/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:33:18 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/28 20:08:39 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

int	terminate_hook(void)
{
	exit(0);
	return (0);
}

int	loop_event(t_main *game)
{
	static long long	time_log = 0;
	long long			curr_time;

	curr_time = current_time_ms();
	if (!(curr_time - time_log > 16))
		return (0);
	time_log = curr_time;
	render_screen(game);
	render_fps(curr_time, game);
	unlock_switch(game);
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->window.img, 0, 0);
	return (0);
}
