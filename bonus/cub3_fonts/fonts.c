/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:12:48 by root              #+#    #+#             */
/*   Updated: 2025/11/28 04:23:21 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	init_fonts(void *g)
{
	t_main		*game;
	t_font_menu	*menu;

	game = (t_main *)g;
	menu = &game->font_menu;
	menu->alagard.color = DEFAULT_FONT_COLOR;
	menu->alagard.font_size = DEFAULT_FONT_SIZE;
	menu->alagard.gap = DEFAULT_FONT_GAP;
	menu->alagard.max_width = 24;
	menu->alagard.sheet = game->gallery.fonts.alagard;
}
