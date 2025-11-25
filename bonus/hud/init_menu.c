/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:50:08 by root              #+#    #+#             */
/*   Updated: 2025/11/26 01:52:51 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud.h"
#include "../main/main.h"
#include <string.h>

void	*init_main_menu(t_main *g, t_main_menu *mmenu)
{    
	g->state = MENU_MAIN;
	mmenu->selected = &mmenu->btn_campaign;
    mmenu->bg_img = g->gallery.menu.bg;
    
    set_button(&g->main_menu.btn_continue, &g->gallery.menu.continue_btn,
	(t_vector){(WIN_WIDTH / 2 - g->gallery.menu.continue_btn.width / 4),
	(WIN_HEIGHT / 2) - (g->gallery.menu.continue_btn.height * 2) / 3 - g->gallery.menu.maps_btn.height * 1.5});

    set_button(&mmenu->btn_campaign, &g->gallery.menu.campaign_btn,
        (t_vector){(WIN_WIDTH / 2 - g->gallery.menu.campaign_btn.width / 4),
            (WIN_HEIGHT / 2) - (g->gallery.menu.campaign_btn.height * 2) / 3});

	set_button(&mmenu->btn_map_select, &g->gallery.menu.maps_btn,
        (t_vector){(WIN_WIDTH / 2 - g->gallery.menu.maps_btn.width / 4),
            (WIN_HEIGHT / 2) - (g->gallery.menu.maps_btn.height * 2) / 3 + g->gallery.menu.maps_btn.height * 1.5});

    set_button(&mmenu->btn_exit, &g->gallery.menu.exit_btn,
        (t_vector){(WIN_WIDTH / 2 - g->gallery.menu.exit_btn.width / 4),
            (WIN_HEIGHT / 2) - (g->gallery.menu.exit_btn.height * 2) / 3 + g->gallery.menu.exit_btn.height * 3});

    return (g);
}
#include <stdio.h>
#include <math.h>
void	*init_map_select_menu(t_main *g, t_map_select *menu)
{
    int files_count;
    int pages;
    int p;
    int s;
    t_vector base;
    t_text txt;
    char *fname;

    menu->bg_img = g->gallery.menu.bg;
    menu->selected = NULL;

    /* count available map files */
    files_count = 0;
    while (g->map.files && g->map.files[files_count].file)
        files_count++;

    if (files_count == 0)
    {
        menu->maps = NULL;
        menu->curr_page = 0;
    }
    else
    {
    pages = ceil((double)(files_count + 4) / MAP_SELECT_PAGE_NUM);
	printf("filescount::%d\npage::%d\n",files_count, pages);
    menu->maps = alloc(sizeof(t_text_button *) * (pages + 1), STATIC);

    base.x = WIN_WIDTH / 4;

    p = 0;
    while (p < pages)
    {
        menu->maps[p] = alloc(sizeof(t_text_button) * MAP_SELECT_PAGE_NUM, STATIC);
        base.y = WIN_HEIGHT / 4;
        s = 0;
        while (s < MAP_SELECT_PAGE_NUM)
        {
            int idx = p * MAP_SELECT_PAGE_NUM + s;
            if (idx < files_count)
            {
                fname = g->map.files[idx].file_shown;
                txt.text_len = strlen(fname);
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
            s++;
        }
        p++;
    }
    menu->maps[p] = NULL;
    menu->curr_page = 0;
    }
    txt.text_len = 1;
    txt.font = &g->font_menu.alagard;
    txt.scale = 5.0;
    txt.win = &g->window;
    txt.win_x = WIN_WIDTH / 10;
    txt.win_y = WIN_HEIGHT / 2;
    set_text_button(&menu->prev_page, txt, (t_vector){WIN_WIDTH / 10, (WIN_HEIGHT / 2) - 40});
    txt.win_x = WIN_WIDTH - (WIN_WIDTH / 5);
    txt.win_y = WIN_HEIGHT / 2;
    set_text_button(&menu->next_page, txt, (t_vector){WIN_WIDTH - (WIN_WIDTH / 5), (WIN_HEIGHT / 2) - 40});

    return (menu);
}

// show up when you complete the map and there is a next map
void	*init_shop_menu(t_main *g, t_shop *menu)
{
    t_text txt;
    int i;

    menu->bg_img = g->gallery.shop.bg;
    menu->selected = NULL;

    txt.font = &g->font_menu.alagard;
    txt.scale = 0.75;
    txt.win = &g->window;
    txt.color = 0xFFFFFFFF; // White
	i = -1;
    while (++i < 6)
    {
        txt.text_len = 30;
        txt.win_x = WIN_WIDTH / 4;
        txt.win_y = 4 * (WIN_HEIGHT / 7) + i * (txt.font->font_size * txt.scale + 8);
        set_text_button(&menu->items[i], txt, (t_vector){txt.win_x, txt.win_y});
    }
	txt.text_len = 9;
	txt.scale = 0.8;
	txt.color = 0xFFFFFFFF;
	txt.win_x = WIN_WIDTH / 2 - (txt.font->font_size * txt.scale * (txt.text_len + 2)) / 3;
	txt.win_y = WIN_HEIGHT / 4 + 8 * (txt.font->font_size * txt.scale + 24);
    set_text_button(&menu->to_continue, txt, (t_vector){txt.win_x, txt.win_y});
    return (menu);
}
// shows up when game session ends no matter if u died or won(somehow)
void	*init_game_summary_menu(t_main *g, t_game_summary *menu)
{
	t_text	txt;

	menu->bg_img = g->gallery.menu.bg;

	// Initialize text properties
	txt.font = &g->font_menu.alagard;
	txt.win = &g->window;
	txt.sheet_row = 0;
	txt.sheet_col = 0;

	// Runtime text
	txt.text_len = 20;
	txt.scale = 1.0;
	txt.color = 0xFFFFFFFF;
	txt.win_x = WIN_WIDTH / 4;
	txt.win_y = WIN_HEIGHT / 4;
	menu->run_time = txt;

	// Kill count text
	txt.text_len = 20;
	txt.win_y = WIN_HEIGHT / 4 + (txt.font->font_size * txt.scale + 20);
	menu->kill_count = txt;

	// Total income text
	txt.text_len = 20;
	txt.win_y = WIN_HEIGHT / 4 + 2 * (txt.font->font_size * txt.scale + 20);
	menu->total_income = txt;

	// Items bought text
	txt.text_len = 30;
	txt.win_y = WIN_HEIGHT / 4 + 3 * (txt.font->font_size * txt.scale + 20);
	menu->items_bought = txt;

	// Continue text
	txt.text_len = 26;
	txt.scale = 0.8;
	txt.color = 0xFFFFFF00;
	txt.win_x = WIN_WIDTH / 2 - (txt.font->font_size * txt.scale * (txt.text_len + 2)) / 3;
	txt.win_y = WIN_HEIGHT / 2 + (WIN_HEIGHT / 4);
	menu->to_continue = txt;

	return (menu);
}
// shows up when map facing with an error while loading map
void	*init_error_menu(t_main *g, t_error *menu)
{
	t_text	txt;

	menu->bg_img = g->gallery.menu.bg;
	
	txt.text_len = 19;
	txt.font = &g->font_menu.alagard;
	txt.scale = 1.5;
	txt.win = &g->window;
	txt.color = 0xFFFF4444;
	txt.win_x = WIN_WIDTH / 2 - (txt.font->font_size * txt.scale * (txt.text_len + 1)) / 3 ;
	txt.win_y = WIN_HEIGHT / 2 - (WIN_HEIGHT / 20);
	txt.sheet_row = 0;
	txt.sheet_col = 0;
	menu->error_text = txt;
	txt.text_len = 26;
	txt.scale = 0.8;
	txt.color = 0xFFFFFFFF;
	txt.win_x = WIN_WIDTH / 2 - (txt.font->font_size * txt.scale * (txt.text_len + 2)) / 3;
	txt.win_y = WIN_HEIGHT / 2 + (WIN_HEIGHT / 5);
	menu->to_continue = txt;
	return (menu);
}
