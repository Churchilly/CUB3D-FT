/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:33:18 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/24 08:01:12 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <stdio.h> // for debug

int terminate_hook(void)
{
	printf("dont kill me :c\n");
	exit(0);
	return (0);
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
	render_screen(game);
	fps_counter(curr_time); // turn it into render fps
	unlock_switch(game);
}
