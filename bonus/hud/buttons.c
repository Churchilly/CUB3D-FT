/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 00:55:21 by root              #+#    #+#             */
/*   Updated: 2025/11/19 23:27:33 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud.h"
#include "../events/events.h"

void *set_button(t_button *button, t_im *img, t_vector pos)
{
    int width;
    int height;

    button->image = *img;
    button->position = pos;
    width = img->width;
    height = img->height;
    width = width / 2;
    button->width = width;
    button->height = height;
    return (button);
}

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


void check_button(t_main *game, t_button *button)
{
    t_vector mouse_pos;
    
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

void	check_text_button(t_main *game, t_text_button *button)
{
    t_vector mouse_pos;

    mouse_pos = get_mouse_position(game);
    if (mouse_pos.x > button->position.x
            && mouse_pos.x < button->position.x + button->width)
    {
        if (mouse_pos.y > button->position.y
            && mouse_pos.y < button->position.y + button->height)
        {
			game->map_select.selected = button;
        }
    }
}

void place_button(t_main *g, t_button *btn)
{
	check_button(g, btn);
	if (btn == g->main_menu.selected)
		draw_button_hover(&g->window, &btn->image, btn->position.x,
				btn->position.y);
	else
		draw_button(&g->window, &btn->image, btn->position.x,
				btn->position.y);
}

static void	draw_rect(t_window *win, int x, int y, int width, int height, int color)
{
	int	px;
	int	py;

	py = 0;
	while (py < height)
	{
		px = 0;
		while (px < width)
		{
			put_pixel(x + px, y + py, color, win);
			px++;
		}
		py++;
	}
}

void	place_text_button(t_main *g, t_text_button *b, char *label)
{
	t_text tmp;

	check_text_button(g, b);
	if (b == g->map_select.selected)
		b->text_data.color = 0xFF0000FF;
	else
		b->text_data.color = b->text_data.font->color;

	tmp = b->text_data;
	tmp.win_x = b->position.x;
	tmp.win_y = b->position.y;
	draw_text(label, &tmp);
}