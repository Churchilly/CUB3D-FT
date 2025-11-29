/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_error_menu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:37:27 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 22:52:13 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

void	*init_error_menu(t_main *g, t_error *menu)
{
	t_text	txt;

	txt.text_len = 19;
	txt.font = &g->font_menu.alagard;
	txt.scale = 2.0;
	txt.win = &g->window;
	txt.color = 0xFFFF4444;
	txt.win_x = WIN_WIDTH / 2 - (txt.font->font_size * txt.scale * (txt.text_len
				+ 1)) / 5;
	txt.win_y = WIN_HEIGHT / 2 - (WIN_HEIGHT / 20);
	txt.sheet_row = 0;
	txt.sheet_col = 0;
	menu->error_text = txt;
	txt.text_len = 26;
	txt.scale = 0.8;
	txt.color = 0xFFFFFFFF;
	txt.win_x = WIN_WIDTH / 2 - (txt.font->font_size * txt.scale * (txt.text_len
				+ 2)) / 3;
	txt.win_y = WIN_HEIGHT / 2 + (WIN_HEIGHT / 5);
	menu->to_continue = txt;
	return (menu);
}
