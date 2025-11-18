/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3_fonts.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:45:23 by root              #+#    #+#             */
/*   Updated: 2025/11/19 00:28:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3_FONTS_H
# define CUB3_FONTS_H
# define DEFAULT_FONT_SIZE 32
# define DEFAULT_FONT_GAP 1
# define DEFAULT_FONT_COLOR 0x00000000
# define CASE_UPPER 1
# define CASE_LOWER 0

# include "../cub3_images/cub3_images.h"
# include <stdbool.h>

typedef struct s_cub3_font t_font;
typedef struct s_font_selector t_font_menu;
typedef struct s_text t_text;
typedef struct s_pos t_pos;

enum e_font_row
{
    ROW_UPPERCASE = 0,
    ROW_LOWERCASE,
    ROW_NUMBER,
    ROW_SYMBOL
};

struct s_cub3_font
{
    t_im sheet;
    int max_width;
    int font_size;
    int color;
    int gap;
};

struct s_font_selector
{
    t_font alagard;
    t_font another_font;
};

struct s_text
{
    int win_x;
    int win_y;
    t_font *font;
    int sheet_row;
    int sheet_col;
    double scale;
    t_window *win;
};

struct s_pos
{
    int x;
    int y;
};

bool is_char(char ch);
bool is_upper(char ch);
bool is_num(char ch);
bool is_symbol(char ch);
void init_fonts(void *g);
void draw_text(char *text, t_font *font, t_pos pos, t_window *win, double scale);

#endif