/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_select_menu.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:32:37 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 18:55:18 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <math.h>
#include <string.h>

static void	init_nav_buttons(t_main *g, t_map_select *menu)
{
	t_text	txt;

	txt.text_len = 1;
	txt.font = &g->font_menu.alagard;
	txt.scale = 5.0;
	txt.win = &g->window;
	txt.win_x = WIN_WIDTH / 10;
	txt.win_y = WIN_HEIGHT / 2;
	set_text_button(&menu->prev_page, txt, (t_vector){WIN_WIDTH / 10,
		(WIN_HEIGHT / 2) - 40});
	txt.win_x = WIN_WIDTH - (WIN_WIDTH / 5);
	txt.win_y = WIN_HEIGHT / 2;
	set_text_button(&menu->next_page, txt, (t_vector){WIN_WIDTH - (WIN_WIDTH
			/ 5), (WIN_HEIGHT / 2) - 40});
}

void	*init_map_select_menu(t_main *g, t_map_select *menu)
{
	int			files_count;
	int			pages;
	int			p;
	int			s;
	t_vector	base;
	t_text		txt;
	int			idx;

	menu->selected = NULL;
	files_count = 0;
	while (g->map.files && g->map.files[files_count].file)
		files_count++;
	pages = ceil((double)(files_count + 4) / MAP_SELECT_PAGE_NUM);
	menu->maps = alloc(sizeof(t_text_button *) * (pages + 1), STATIC);
	base.x = WIN_WIDTH / 4;
	p = -1;
	while (++p < pages)
	{
		menu->maps[p] = alloc(sizeof(t_text_button) * MAP_SELECT_PAGE_NUM,
				STATIC);
		base.y = WIN_HEIGHT / 4;
		s = -1;
		while (++s < MAP_SELECT_PAGE_NUM)
		{
			idx = p * MAP_SELECT_PAGE_NUM + s;
			if (idx < files_count)
			{
				txt.text_len = strlen(g->map.files[idx].file_shown);
				txt.font = &g->font_menu.alagard;
				txt.scale = 1.0;
				txt.win = &g->window;
				txt.win_x = base.x;
				txt.win_y = base.y;
				set_text_button(&menu->maps[p][s], txt, base);
				base.y += (txt.font->font_size * txt.scale) + 16;
			}
			else
			{
				menu->maps[p][s].width = 0;
				menu->maps[p][s].height = 0;
			}
		}
	}
	menu->maps[p] = NULL;
	menu->curr_page = 0;
	init_nav_buttons(g, menu);
	return (menu);
}
