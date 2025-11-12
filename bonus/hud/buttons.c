/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 00:55:21 by root              #+#    #+#             */
/*   Updated: 2025/11/12 18:04:40 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud.h"
#include "../events/events.h"

void *set_button(t_button *button, bool hover, t_im *img, t_vector pos)
{
    int width;
    int height;

    button->hover = hover; // null check falan filan
    button->image = *img;
    button->position = pos;
    width = img->width;
    height = img->height;
    if (hover)
        width = width / 2;
    button->width = width;
    button->height = height;
    button->active = false;
    return (button);
}

void check_button(t_main *game, t_button *button)
{
    t_vector mouse_pos;
    bool result;
    
    mouse_pos = get_mouse_position(game);
    result = false;
    if (mouse_pos.x > button->position.x
            && mouse_pos.x < button->position.x + button->width)
    {
        if (mouse_pos.y > button->position.y
            && mouse_pos.y < button->position.y + button->height)
        {
            result = true;
        }
    }
    button->active = result;
}

void place_button(t_main *g, t_button *btn)
{
	check_button(g, btn);
	if (btn->active)
		draw_button_hover(&g->window, &btn->image, btn->position.x,
				btn->position.y);
	else
		draw_button(&g->window, &btn->image, btn->position.x,
				btn->position.y);
}

void activate_button(t_main *g, t_button *btn)
{
    if (btn == &g->main_menu.btn_start)
    {
        switch_main_menu(g);
        g->key_list.f3.key_switch = true;
    }
    else if (btn == &g->main_menu.btn_exit)
        terminate_hook();
}

bool is_xy_on_button(int x, int y, t_button *btn)
{
    if (x > btn->position.x && x < btn->position.x + btn->width)
        if (y > btn->position.y && y < btn->position.y + btn->height)
            return (true);
    return (false);
}
