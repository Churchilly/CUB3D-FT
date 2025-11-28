/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:49:50 by root              #+#    #+#             */
/*   Updated: 2025/11/28 19:32:08 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../render/render.h"
#include "../utils/utils.h"
#include "cub3_fonts.h"
#include <stdbool.h>
#include <stdio.h>

static int	draw_from_sheet(t_text_int *t)
{
	t_vector_int	scaled;
	t_vector_int	orig;
	int				pixel;

	scaled.y = -1;
	while (++scaled.y < t->size.y)
	{
		orig.y = (int)(scaled.y / t->text->scale);
		scaled.x = -1;
		while (++scaled.x < t->size.x)
		{
			orig.x = (int)(scaled.x / t->text->scale);
			pixel = t->sheet->image[(t->text->sheet_row
					* t->text->font->font_size + orig.y) * t->sheet->width
				+ (t->text->sheet_col * t->text->font->max_width) + orig.x];
			if ((unsigned int)pixel == 0x000000ff)
				put_pixel(t->text->win_x + scaled.x, t->text->win_y + scaled.y,
					t->text->color, t->text->win);
			else if ((unsigned int)pixel == 0xffffffff)
				break ;
		}
	}
	return (scaled.x + DEFAULT_FONT_GAP);
}

static int	draw_char(char ch, bool upper, t_text_int *text)
{
	if (upper)
	{
		text->text->sheet_row = ROW_UPPERCASE;
		text->text->sheet_col = ch - 'A';
	}
	else
	{
		text->text->sheet_row = ROW_LOWERCASE;
		text->text->sheet_col = ch - 'a';
	}
	return (draw_from_sheet(text));
}

static int	draw_number(int num, t_text_int *text)
{
	text->text->sheet_row = ROW_NUMBER;
	text->text->sheet_col = num - '0';
	return (draw_from_sheet(text));
}

static int	draw_symbol(int sym, t_text_int *text)
{
	if (sym == ' ')
		return (5);
	text->text->sheet_row = ROW_SYMBOL;
	text->text->sheet_col = sym - ' ';
	return (draw_from_sheet(text));
}

void	draw_text(char *text, t_text text_data)
{
	int			counter;
	t_text_int	text_int;

	text_int.text = &text_data;
	text_int.sheet = &text_data.font->sheet;
	text_int.size.x = (text_data.font->max_width * text_data.scale);
	text_int.size.y = (int)(text_data.font->font_size * text_data.scale);
	counter = 0;
	while (text[counter])
	{
		if (is_char(text[counter]))
			text_data.win_x += text_data.font->gap + draw_char(text[counter],
					is_upper(text[counter]), &text_int);
		else if (is_num(text[counter]))
			text_data.win_x += text_data.font->gap + draw_number(text[counter],
					&text_int);
		else if (is_symbol(text[counter]))
			text_data.win_x += text_data.font->gap + draw_symbol(text[counter],
					&text_int);
		counter++;
	}
}
