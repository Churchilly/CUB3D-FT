/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:49:50 by root              #+#    #+#             */
/*   Updated: 2025/11/24 09:40:01 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3_fonts.h"
#include "../utils/utils.h"
#include "../render/render.h"
#include <stdbool.h>
#include <stdio.h>

static int draw_from_sheet(t_text *text)
{
    t_vector_int scaled;
    t_vector_int orig;
    t_vector_int size;
    t_im *sheet;
    int pixel;
    
    sheet = &text->font->sheet;
    size.x = (text->font->max_width * text->scale);
    size.y = (int)(text->font->font_size * text->scale);
    scaled.y = -1;
    while (++scaled.y < size.y)
    {
        orig.y = (int)(scaled.y / text->scale);
        scaled.x = -1;
        while (++scaled.x < size.x)
        {
            orig.x = (int)(scaled.x / text->scale);
            pixel = sheet->image[(text->sheet_row * text->font->font_size + orig.y) *
                sheet->width + (text->sheet_col * text->font->max_width) + orig.x];
            if ((unsigned int)pixel == 0x000000ff)
                put_pixel(text->win_x + scaled.x, text->win_y + scaled.y, text->color, text->win);
            else if ((unsigned int)pixel == 0xffffffff)
                break ;
        }
    }
    return (scaled.x + DEFAULT_FONT_GAP);
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
    if (sym == ' ')
        return (5);
    text->sheet_row = ROW_SYMBOL;
    text->sheet_col = sym - ' ';
    return (draw_from_sheet(text));
}

void draw_text(char *text, t_text text_data)
{
    int counter;

    //if (!text || !text_data || !text_data->font || !text_data->win)
    //    return;

    counter = 0;
    while (text[counter])
    {
        if (is_char(text[counter]))
            text_data.win_x += text_data.font->gap + draw_char(text[counter], is_upper(text[counter]), &text_data);
        else if (is_num(text[counter]))
            text_data.win_x += text_data.font->gap + draw_number(text[counter], &text_data);
        else if (is_symbol(text[counter]))
            text_data.win_x += text_data.font->gap + draw_symbol(text[counter], &text_data);
        counter++;
    }
}
