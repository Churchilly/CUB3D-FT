/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_error_menu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:00:53 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 20:01:18 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

void	render_error_menu(t_main *g)
{
	static double	scale_dir = 0.0075;

	draw_image_no_alpha(&g->window, &g->gallery.menu_bg.error, 0, 0);
	draw_text("Failed to load map", g->error_menu.error_text);
	g->error_menu.to_continue.scale += scale_dir;
	g->error_menu.to_continue.win_x = WIN_WIDTH * 4 / 9
		- (g->error_menu.to_continue.font->max_width
			* g->error_menu.to_continue.scale
			* (g->error_menu.to_continue.text_len) / 3);
	if (g->error_menu.to_continue.scale >= 1.0)
		scale_dir = -0.005;
	else if (g->error_menu.to_continue.scale <= 0.75)
		scale_dir = 0.0075;
	draw_text("Press any key to continue", g->error_menu.to_continue);
}
