/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shop_menu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:41:35 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 19:42:01 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

void	*init_shop_menu(t_main *g, t_shop *menu)
{
	t_text	txt;
	int		i;

	menu->selected = NULL;
	txt.font = &g->font_menu.alagard;
	txt.scale = 0.75;
	txt.win = &g->window;
	txt.color = 0xFFFFFFFF;
	i = -1;
	while (++i < 6)
	{
		txt.text_len = 30;
		txt.win_x = WIN_WIDTH / 4;
		txt.win_y = 4 * (WIN_HEIGHT / 7) + i * (txt.font->font_size * txt.scale
				+ 8);
		set_text_button(&menu->items[i], txt, (t_vector){txt.win_x, txt.win_y});
	}
	txt.text_len = 9;
	txt.scale = 0.8;
	txt.color = 0xFFFFFFFF;
	txt.win_x = WIN_WIDTH / 2 - (txt.font->font_size * txt.scale * (txt.text_len
				+ 2)) / 3;
	txt.win_y = WIN_HEIGHT / 4 + 8 * (txt.font->font_size * txt.scale + 24);
	set_text_button(&menu->to_continue, txt, (t_vector){txt.win_x, txt.win_y});
	return (menu);
}
