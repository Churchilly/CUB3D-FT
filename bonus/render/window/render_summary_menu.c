/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_summary_menu.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:03:12 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 22:31:09 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <stdio.h>

static void	draw_animated_text(t_main *g)
{
	static double	scale_dir = 0.0075;

	g->summary_menu.to_continue.scale += scale_dir;
	g->summary_menu.to_continue.win_x = WIN_WIDTH * 4 / 9
		- (g->summary_menu.to_continue.font->max_width
			* g->summary_menu.to_continue.scale
			* (g->summary_menu.to_continue.text_len) / 3);
	if (g->summary_menu.to_continue.scale >= 1.0)
		scale_dir = -0.005;
	else if (g->summary_menu.to_continue.scale <= 0.75)
		scale_dir = 0.0075;
	draw_text("Press any key to continue", g->summary_menu.to_continue);
}

void	render_summary_menu(t_main *g)
{
	char			buf[64];
	int				minutes;
	int				seconds;

	draw_image_no_alpha(&g->window, &g->gallery.menu_bg.summary, 0, 0);
	minutes = (g->record.play_time) / 60;
	seconds = (g->record.play_time) % 60;
	snprintf(buf, sizeof(buf), "Time: %02d:%02d", minutes, seconds);
	draw_text(buf, g->summary_menu.run_time);
	snprintf(buf, sizeof(buf), "Enemies Killed: %u", g->record.kill_count);
	draw_text(buf, g->summary_menu.kill_count);
	snprintf(buf, sizeof(buf), "Total Income: %u", g->record.total_income);
	draw_text(buf, g->summary_menu.total_income);
	snprintf(buf, sizeof(buf), "Items Bought: %u", g->record.purchase_count);
	draw_text(buf, g->summary_menu.items_bought);
	draw_animated_text(g);
}
