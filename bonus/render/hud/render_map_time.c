/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_time.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:15:12 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 19:53:51 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <stdio.h>

void	render_map_time(t_main *g)
{
	char		buf[64];
	int			minutes;
	int			seconds;
	long long	timer;

	timer = (GAME_TIME - g->map.map_timer);
	minutes = (timer) / 60;
	seconds = (timer) % 60;
	snprintf(buf, sizeof(buf), "%02d:%02d", minutes, seconds);
	draw_text(buf, (t_text){2, (WIN_WIDTH / 2) - g->font_menu.alagard.font_size
		* 1.5, 20, &g->font_menu.alagard, 0, 0, 1, &g->window, 0xFFFFFFFF});
}
