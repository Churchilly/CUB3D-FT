/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pause_menu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:00:51 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 20:02:31 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

void	render_pause_menu(t_main *g)
{
	draw_image_no_alpha(&g->window, &g->gallery.menu_bg.pause, 0, 0);
	place_button(g, &g->main_menu.btn_continue);
	place_button(g, &g->main_menu.btn_campaign);
	place_button(g, &g->main_menu.btn_map_select);
	place_button(g, &g->main_menu.btn_exit);
}
