/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_select_menu.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:32:37 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 19:42:07 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <math.h>
#include <string.h>

static int	count_map_files(t_main *g)
{
	int	count;

	count = 0;
	while (g->map.files && g->map.files[count].file)
		count++;
	return (count);
}

static void	init_map_button(t_main *g, t_text_button *btn, t_vector base,
		int idx)
{
	t_text	txt;

	txt.text_len = strlen(g->map.files[idx].file_shown);
	txt.font = &g->font_menu.alagard;
	txt.scale = 1.0;
	txt.win = &g->window;
	txt.win_x = base.x;
	txt.win_y = base.y;
	set_text_button(btn, txt, base);
}

static void	init_map_page(t_main *g, t_text_button *page, int page_num,
		int files_count)
{
	t_vector	base;
	int			s;
	int			idx;

	s = 0;
	base.x = WIN_WIDTH / 4;
	base.y = WIN_HEIGHT / 4;
	while (s < MAP_SELECT_PAGE_NUM)
	{
		idx = page_num * MAP_SELECT_PAGE_NUM + s;
		if (idx < files_count)
		{
			init_map_button(g, &page[s], base, idx);
			base.y += (g->font_menu.alagard.font_size * 1.0) + 16;
		}
		else
		{
			page[s].width = 0;
			page[s].height = 0;
		}
		s++;
	}
}

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
	int	files_count;
	int	pages;
	int	p;

	files_count = count_map_files(g);
	pages = ceil((double)(files_count + 4) / MAP_SELECT_PAGE_NUM);
	menu->selected = NULL;
	menu->maps = alloc(sizeof(t_text_button *) * (pages + 1), STATIC);
	p = 0;
	while (p < pages)
	{
		menu->maps[p] = alloc(sizeof(t_text_button) * MAP_SELECT_PAGE_NUM,
				STATIC);
		init_map_page(g, menu->maps[p], p, files_count);
		p++;
	}
	menu->maps[p] = NULL;
	menu->curr_page = 0;
	init_nav_buttons(g, menu);
	return (menu);
}
