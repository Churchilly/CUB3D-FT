/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:33:18 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/28 21:21:52 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <stdio.h>

int	terminate_hook(void)
{
	exit(0);
	return (0);
}

static void	render_fps(long long curr_time, t_main *g)
{
	static int			frame_count = 1;
	static long long	time_log = 0;
	static char			buf[4];

	frame_count++;
	if (curr_time - time_log >= 1000)
	{
		snprintf(buf, sizeof(buf), "%d", frame_count);
		frame_count = 1;
		time_log = curr_time;
	}
	draw_text(buf, (t_text){2, WIN_WIDTH - 60, 20, &g->font_menu.alagard, 0, 0,
		1, &g->window, 0xFFFFFFFF});
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
