/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_render_frames.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 08:54:49 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/16 09:01:15 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

static int get_pixel_from_window(t_window *win, int x, int y)
{
    char *dst;

    if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        return (0);
    dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
    return (*(unsigned int *)dst);
}

static void draw_frame_with_alpha(t_window *win, t_cub3_image *img, double alpha)
{
    int x;
    int y;
    int color;
    int bg_color;
    int blended;

    y = 0;
    while (y < img->height && y < WIN_HEIGHT)
    {
        x = 0;
        while (x < img->width && x < WIN_WIDTH)
        {
            color = img->image[y * img->width + x];
            if ((unsigned int)color != 0xffffffff)
            {
                // Remove alpha channel (shift right by 8 bits to convert RGBA to RGB)
                color = (color >> 8) & 0x00FFFFFF;
                bg_color = get_pixel_from_window(win, x, y);
                blended = blend_alpha(bg_color, color, alpha);
                put_pixel(x, y, blended, win);
            }
            x++;
        }
        y++;
    }
}

void render_frames(t_main *g)
{
    t_im *frame;
    t_player *player;

    player = &g->map.player;
    if (player->health < 20)
        frame = &g->gallery.frames.low_hp_3;
    else if (player->health < 50)
        frame = &g->gallery.frames.low_hp_2;
    else if (player->health < 80)
        frame = &g->gallery.frames.low_hp_1;
    else
        return ;
    draw_frame_with_alpha(&g->window, frame, 0.3);
}
