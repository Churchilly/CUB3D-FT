/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_select.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 03:32:58 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/20 01:01:38 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include "../events/events.h"

void	next_button(t_main *g)
{
	if (g->state == MENU_MAIN || g->state == MENU_PAUSE)
	{
		if (g->main_menu.selected == &(g->main_menu.btn_continue))
			g->main_menu.selected = &(g->main_menu.btn_campaign);
		else if (g->main_menu.selected == &(g->main_menu.btn_campaign))
			g->main_menu.selected = &(g->main_menu.btn_map_select);
		else if (g->main_menu.selected == &(g->main_menu.btn_map_select))
			g->main_menu.selected = &(g->main_menu.btn_exit);
		else if (g->main_menu.selected == &(g->main_menu.btn_exit))
		{
			if (g->main_menu.btn_continue.height != -1)
				g->main_menu.selected = &(g->main_menu.btn_continue);
			else
				g->main_menu.selected = &(g->main_menu.btn_campaign);
		}
	}
	else if (g->state == MENU_MAP_SELECT)
	{
		t_text_button *page;
		int files_count;
		int current_idx;
		int i;

		if (!g->map_select.maps)
			return;
		
		page = g->map_select.maps[g->map_select.curr_page];
		if (!page)
			return;

		files_count = 0;
		while (g->map.files && g->map.files[files_count].file)
			files_count++;

		if (!g->map_select.selected)
		{
			i = 0;
			while (i < MAP_SELECT_PAGE_NUM)
			{
				if (page[i].width > 0)
				{
					g->map_select.selected = &page[i];
					return;
				}
				i++;
			}
			return;
		}

		current_idx = -1;
		i = 0;
		while (i < MAP_SELECT_PAGE_NUM)
		{
			if (&page[i] == g->map_select.selected)
			{
				current_idx = i;
				break;
			}
			i++;
		}

		/* move to next item */
		if (current_idx >= 0 && current_idx < MAP_SELECT_PAGE_NUM - 1)
		{
			i = current_idx + 1;
			while (i < MAP_SELECT_PAGE_NUM)
			{
				if (page[i].width > 0)
				{
					g->map_select.selected = &page[i];
					return;
				}
				i++;
			}
		}

		/* wrap to first item */
		i = 0;
		while (i < MAP_SELECT_PAGE_NUM)
		{
			if (page[i].width > 0)
			{
				g->map_select.selected = &page[i];
				return;
			}
			i++;
		}
	}
}

void	prev_button(t_main *g)
{
	if (g->state == MENU_MAIN || g->state == MENU_PAUSE)
	{
		if (g->main_menu.selected == &(g->main_menu.btn_continue))
			g->main_menu.selected = &(g->main_menu.btn_exit);
		else if (g->main_menu.selected == &(g->main_menu.btn_campaign))
		{
			if (g->main_menu.btn_continue.height != -1)
				g->main_menu.selected = &(g->main_menu.btn_continue);
			else
				g->main_menu.selected = &(g->main_menu.btn_exit);
		}
		else if (g->main_menu.selected == &(g->main_menu.btn_map_select))
			g->main_menu.selected = &(g->main_menu.btn_campaign);
		else if (g->main_menu.selected == &(g->main_menu.btn_exit))
			g->main_menu.selected = &(g->main_menu.btn_map_select);
	}
	else if (g->state == MENU_MAP_SELECT)
	{
		t_text_button *page;
		int current_idx;
		int i;

		if (!g->map_select.maps)
			return;
		
		page = g->map_select.maps[g->map_select.curr_page];
		if (!page)
			return;

		if (!g->map_select.selected)
		{
			i = 0;
			while (i < MAP_SELECT_PAGE_NUM)
			{
				if (page[i].width > 0)
				{
					g->map_select.selected = &page[i];
					return;
				}
				i++;
			}
			return;
		}

		/* find current selection index on page */
		current_idx = -1;
		i = 0;
		while (i < MAP_SELECT_PAGE_NUM)
		{
			if (&page[i] == g->map_select.selected)
			{
				current_idx = i;
				break;
			}
			i++;
		}

		/* move to previous item */
		if (current_idx > 0)
		{
			i = current_idx - 1;
			while (i >= 0)
			{
				if (page[i].width > 0)
				{
					g->map_select.selected = &page[i];
					return;
				}
				i--;
			}
		}

		/* wrap to last item */
		i = MAP_SELECT_PAGE_NUM - 1;
		while (i >= 0)
		{
			if (page[i].width > 0)
			{
				g->map_select.selected = &page[i];
				return;
			}
			i--;
		}
	}
}


void activate_button(t_main *g)
{

	if (g->state == MENU_MAIN || g->state == MENU_PAUSE)
	{
    	if (g->main_menu.selected == &g->main_menu.btn_campaign)
    	{
			init_game(g, CAMPAIGN_MAP);
			if (g->main_menu.btn_continue.height == -1)
			{
    			set_button(&g->main_menu.btn_continue,
					&g->gallery.mmenu_start_btn,
    	    		(t_vector){(WIN_WIDTH / 2
					- g->gallery.mmenu_start_btn.width / 4),
    	    	    (WIN_HEIGHT / 2) - (g->gallery.mmenu_start_btn.height * 2)
					/ 3 - g->gallery.mmenu_start_btn.height});
			}
			switch_menu(g);
    	    g->key_list.f3.key_switch = true;
    	}
		else if (g->main_menu.selected == &g->main_menu.btn_continue)
			switch_menu(g);
		else if (g->main_menu.selected == &(g->main_menu.btn_map_select))
			g->state = MENU_MAP_SELECT;
    	else if (g->main_menu.selected == &g->main_menu.btn_exit)
    	    terminate_hook();
	}
	else if (g->state == MENU_MAP_SELECT)
	{
		t_text_button *page;
		int i;
		int idx;
		
		if (!g->map_select.maps)
			return;

		page = g->map_select.maps[g->map_select.curr_page];
		if (!page)
			return;

		if (g->map_select.selected)
		{
			i = 0;
			while (i < MAP_SELECT_PAGE_NUM)
			{
				if (&page[i] == g->map_select.selected && page[i].width > 0)
				{
					idx = g->map_select.curr_page * MAP_SELECT_PAGE_NUM + i;
					if (g->map.files[idx].file)
					{
						init_game(g, g->map.files[idx].file);
						if (g->main_menu.btn_continue.height == -1)
						{
    						set_button(&g->main_menu.btn_continue,
								&g->gallery.mmenu_start_btn,
    	    					(t_vector){(WIN_WIDTH / 2
								- g->gallery.mmenu_start_btn.width / 4),
    	    				    (WIN_HEIGHT / 2) - (g->gallery.mmenu_start_btn.height * 2)
								/ 3 - g->gallery.mmenu_start_btn.height});
						}
						switch_menu(g);
						g->key_list.f3.key_switch = true;
					}
					return;
				}
				i++;
			}
		}
	}
}

void	next_page(t_main *g)
{
	int files_count;
	int max_page;

	files_count = 0;
	while (g->map.files && g->map.files[files_count].file)
		files_count++;
	max_page = files_count / MAP_SELECT_PAGE_NUM;
	if (g->map_select.curr_page < max_page)
	{
		g->map_select.curr_page++;
		g->map_select.selected = &(g->map_select.maps[g->map_select.curr_page][0]);
	}
	else
	{
		g->map_select.curr_page = 0;
		g->map_select.selected = &(g->map_select.maps[g->map_select.curr_page][0]);
	}
}

void	prev_page(t_main *g)
{
	int files_count;
	int max_page;

	files_count = 0;
	while (g->map.files && g->map.files[files_count].file)
		files_count++;
	max_page = files_count / MAP_SELECT_PAGE_NUM;
	if (g->map_select.curr_page > 0)
	{
		g->map_select.curr_page--;
		g->map_select.selected = &(g->map_select.maps[g->map_select.curr_page][0]);
	}
	else
	{
		g->map_select.curr_page = max_page;
		g->map_select.selected = &(g->map_select.maps[g->map_select.curr_page][0]);
	}
}
