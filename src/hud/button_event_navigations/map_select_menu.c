/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_select_menu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 21:38:46 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/24 08:07:11 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

void	next_map_select_item(t_main *g)
{
	t_text_button	*page;
	int				i;
	int				start;

	page = g->map_select.maps[g->map_select.curr_page];
	if (!page)
		return ;
	start = 0;
	if (g->map_select.selected)
	{
		i = -1;
		while (++i < MAP_SELECT_PAGE_NUM)
			if (&page[i] == g->map_select.selected)
				start = i + 1;
	}
	i = start - 1;
	while (++i < MAP_SELECT_PAGE_NUM)
		if (page[i].width > 0)
			return ((void)(g->map_select.selected = &page[i]));
	i = -1;
	while (++i < start)
		if (page[i].width > 0)
			return ((void)(g->map_select.selected = &page[i]));
}

void	prev_map_select_item(t_main *g)
{
	t_text_button	*page;
	int				i;
	int				start;

	page = g->map_select.maps[g->map_select.curr_page];
	if (!page)
		return ;
	start = MAP_SELECT_PAGE_NUM;
	if (g->map_select.selected)
	{
		i = -1;
		while (++i < MAP_SELECT_PAGE_NUM)
			if (&page[i] == g->map_select.selected)
				start = i;
	}
	i = start;
	while (--i >= 0)
		if (page[i].width > 0)
			return ((void)(g->map_select.selected = &page[i]));
	i = MAP_SELECT_PAGE_NUM;
	while (--i >= start)
		if (page[i].width > 0)
			return ((void)(g->map_select.selected = &page[i]));
}

void	activate_button_map_select(t_main *g)
{
	t_text_button	*page;
	int				i;
	int				idx;

	page = g->map_select.maps[g->map_select.curr_page];
	if (!page)
		return ;
	if (g->map_select.selected)
	{
		i = 0;
		while (i < MAP_SELECT_PAGE_NUM)
		{
			if (&page[i] == g->map_select.selected && page[i].width > 0)
			{
				idx = g->map_select.curr_page * MAP_SELECT_PAGE_NUM + i;
				if (g->map.files[idx].file)
					new_game(g, g->map.files[idx].file);
				return ;
			}
			i++;
		}
	}
}

void	next_page(t_main *g)
{
	int	files_count;
	int	max_page;

	files_count = 0;
	while (g->map.files && g->map.files[files_count].file)
		files_count++;
	max_page = files_count / MAP_SELECT_PAGE_NUM;
	if (g->map_select.curr_page < max_page)
	{
		g->map_select.curr_page++;
		g->map_select.selected
			= &(g->map_select.maps[g->map_select.curr_page][0]);
	}
	else
	{
		g->map_select.curr_page = 0;
		g->map_select.selected
			= &(g->map_select.maps[g->map_select.curr_page][0]);
	}
}

void	prev_page(t_main *g)
{
	int	files_count;
	int	max_page;

	files_count = 0;
	while (g->map.files && g->map.files[files_count].file)
		files_count++;
	max_page = files_count / MAP_SELECT_PAGE_NUM;
	if (g->map_select.curr_page > 0)
	{
		g->map_select.curr_page--;
		g->map_select.selected
			= &(g->map_select.maps[g->map_select.curr_page][0]);
	}
	else
	{
		g->map_select.curr_page = max_page;
		g->map_select.selected
			= &(g->map_select.maps[g->map_select.curr_page][0]);
	}
}
