/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:07:26 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 20:08:26 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <stdio.h>

void	render_fps(long long curr_time, t_main *g)
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
	draw_text(buf,
		(t_text){2, WIN_WIDTH - 60, 20,
		&g->font_menu.alagard, 0, 0, 1, &g->window, 0xFFFFFFFF});
}
