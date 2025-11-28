/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_select_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:02:35 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 22:31:34 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

void	render_select_map(t_main *g)
{
	t_text_button	*page;
	int				i;
	int				idx;

	draw_image_no_alpha_scaled(&g->window, &g->gallery.menu_bg.map_select,
		(t_pos){-80, -80}, .4);
	page = NULL;
	if (g->map_select.maps && g->map_select.curr_page >= 0)
		page = g->map_select.maps[g->map_select.curr_page];
	i = 0;
	while (i < MAP_SELECT_PAGE_NUM)
	{
		if (page && page[i].width > 0)
		{
			idx = g->map_select.curr_page * MAP_SELECT_PAGE_NUM + i;
			place_text_button(g, &page[i], g->map.files[idx].file_shown);
		}
		i++;
	}
	place_text_button(g, &g->map_select.prev_page, "<");
	place_text_button(g, &g->map_select.next_page, ">");
}
