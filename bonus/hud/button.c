/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 00:55:21 by root              #+#    #+#             */
/*   Updated: 2025/11/22 05:39:48 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud.h"
#include "../events/events.h"

void	*set_button(t_button *button, t_im *img, t_vector pos)
{
	int	width;
	int	height;

	button->image = *img;
	button->position = pos;
	width = img->width;
	height = img->height;
	width = width / 2;
	button->width = width;
	button->height = height;
	return (button);
}

void	check_button(t_main *game, t_button *button)
{
	t_vector	mouse_pos;

	mouse_pos = get_mouse_position(game);
	if (mouse_pos.x > button->position.x
		&& mouse_pos.x < button->position.x + button->width)
	{
		if (mouse_pos.y > button->position.y
			&& mouse_pos.y < button->position.y + button->height)
		{
			game->main_menu.selected = button;
		}
	}
}

void	place_button(t_main *g, t_button *btn)
{
	check_button(g, btn);
	if (btn == g->main_menu.selected)
		draw_button_hover(&g->window, &btn->image, btn->position.x,
			btn->position.y);
	else
		draw_button(&g->window, &btn->image, btn->position.x,
			btn->position.y);
}
