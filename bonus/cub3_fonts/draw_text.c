/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:49:50 by root              #+#    #+#             */
/*   Updated: 2025/11/19 01:22:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3_fonts.h"
#include "../utils/utils.h"
#include "../render/render.h"
#include <stdbool.h>
#include <stdio.h>

static int draw_from_sheet(t_text *text)
{
    int scaled_px;
    int scaled_py;
    int original_px;
    int original_py;
    int pixel;
    t_im *image;
    int scaled_height;
    int scaled_width;

    image = &text->font->sheet;
    scaled_height = (int)(text->font->font_size * text->scale);
    scaled_width = (int)(text->font->max_width * text->scale);

    scaled_py = 0;
    while (scaled_py < scaled_height)
    {
        original_py = (int)(scaled_py / text->scale);
        scaled_px = 0;
        while (scaled_px < scaled_width)
        {
            original_px = (int)(scaled_px / text->scale);
            pixel = image->image[(text->sheet_row * text->font->font_size + original_py) *
                image->width + (text->sheet_col * text->font->max_width) + original_px];
            if (pixel == 0x000000ff)
                put_pixel(text->win_x + scaled_px, text->win_y + scaled_py, 0x000000, text->win);
            scaled_px++;
        }
        scaled_py++;
    }
    return (scaled_width);
}

static int draw_char(char ch, bool upper, t_text *text)
{
    if (upper)
    {
        text->sheet_row = ROW_UPPERCASE;
        text->sheet_col = ch - 'A'; 
    }
    else
    {
        text->sheet_row = ROW_LOWERCASE;
        text->sheet_col = ch - 'a';
    }
    return (draw_from_sheet(text));
}

static int draw_number(int num, t_text *text)
{
    text->sheet_row = ROW_NUMBER;
    text->sheet_col = num - '0';
    return (draw_from_sheet(text));
}

static int draw_symbol(int sym, t_text *text)
{
    text->sheet_row = ROW_SYMBOL;
    text->sheet_col = sym - ' ';
    return (draw_from_sheet(text));
}

void draw_text(char *text, t_font *font, t_pos pos, t_window *win, double scale)
{
    t_text text_t;
    int counter;

    text_t.font = font;
    text_t.win_x = pos.x;
    text_t.win_y = pos.y;
    text_t.scale = scale;
    text_t.win = win;
    
    counter = 0;
    while (text[counter])
    {
        if (is_char(text[counter]))
            text_t.win_x += font->gap + draw_char(text[counter], is_upper(text[counter]), &text_t);
        else if (is_num(text[counter]))
            text_t.win_x += font->gap + draw_number(text[counter], &text_t);
        else if (is_symbol(text[counter]))
            text_t.win_x += font->gap + draw_symbol(text[counter], &text_t);
        counter++;
    }
}
