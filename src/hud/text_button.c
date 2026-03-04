/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_button.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 05:35:40 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 17:34:51 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include "hud.h"

void	*set_text_button(t_text_button *button, t_text text_data, t_vector pos)
{
	int	font_w;
	int	font_h;

	button->position = pos;
	button->text_data = text_data;
	button->text_data.win_x = pos.x;
	button->text_data.win_y = pos.y;
	if (text_data.font)
	{
		font_w = text_data.font->max_width;
		font_h = text_data.font->font_size;
	}
	else
	{
		font_w = DEFAULT_FONT_SIZE;
		font_h = DEFAULT_FONT_SIZE;
	}
	button->width = (int)(font_w * text_data.scale * text_data.text_len);
	button->height = (int)(font_h * text_data.scale);
	return (button);
}

void	check_text_button(t_main *game, t_text_button *button)
{
	t_vector	mouse_pos;

	mouse_pos = get_mouse_position(game);
	if (mouse_pos.x > button->position.x && mouse_pos.x < button->position.x
		+ button->width)
	{
		if (mouse_pos.y > button->position.y && mouse_pos.y < button->position.y
			+ button->height)
		{
			if (game->state == MENU_MAP_SELECT)
				game->map_select.selected = button;
			else if (game->state == MENU_SHOP)
				game->shop_menu.selected = button;
		}
	}
}

void	place_text_button(t_main *g, t_text_button *b, char *label)
{
	t_text	tmp;

	check_text_button(g, b);
	if (b == g->map_select.selected || b == g->shop_menu.selected)
		b->text_data.color = 0xFF0000FF;
	else
		b->text_data.color = b->text_data.font->color;
	tmp = b->text_data;
	tmp.win_x = b->position.x;
	tmp.win_y = b->position.y;
	draw_text(label, tmp);
}
