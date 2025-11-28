/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_summary_menu.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:37:48 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 18:32:13 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

static void	init_menu_texts(t_game_summary *menu, t_text txt)
{
	txt.text_len = 16;
	txt.scale = 1.0;
	txt.color = 0xFFFFFFFF;
	txt.win_x = WIN_WIDTH / 3;
	txt.win_y = WIN_HEIGHT / 3 + (txt.font->font_size * txt.scale + 20) * 2;
	menu->run_time = txt;
	txt.text_len = 21;
	txt.win_y += (txt.font->font_size * txt.scale + 20);
	menu->kill_count = txt;
	txt.text_len = 20;
	txt.win_y += (txt.font->font_size * txt.scale + 20);
	menu->total_income = txt;
	txt.text_len = 30;
	txt.win_y += (txt.font->font_size * txt.scale + 20);
	menu->items_bought = txt;
	txt.text_len = 26;
	txt.scale = 0.8;
	txt.color = 0xFFFFFF00;
	txt.win_y = WIN_HEIGHT - (WIN_HEIGHT / 10);
	menu->to_continue = txt;
}

void	*init_game_summary_menu(t_main *g, t_game_summary *menu)
{
	t_text	txt;

	txt.font = &g->font_menu.alagard;
	txt.win = &g->window;
	txt.sheet_row = 0;
	txt.sheet_col = 0;
	init_menu_texts(menu, txt);
	return (menu);
}
