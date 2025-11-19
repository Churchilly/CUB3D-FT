/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 05:39:18 by root              #+#    #+#             */
/*   Updated: 2025/11/20 00:18:35 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <math.h>

void draw_image(t_window *win, t_cub3_image *img, int x, int y)
{
    int x1;
    int y1;
    int counter;

    x1 = 0;
    y1 = 0;
    counter = 0;
    while (counter < (img->height * img->width))
    {
        if (counter != 0 && counter % img->width == 0)
        {
            x1 = 0;
            y1 = y1 + 1;
        }
        if (((unsigned int)img->image[counter]) != 0xffffffff)
            put_pixel(x1 + x, y1 + y, img->image[counter], win);
        x1++;
        counter++;
    }
}

void draw_image_no_alpha(t_window *win, t_cub3_image *img, int x, int y)
{
    int x1;
    int y1;
    int counter;

    x1 = 0;
    y1 = 0;
    counter = 0;
    while (counter < (img->height * img->width))
    {
        if (counter != 0 && counter % img->width == 0)
        {
            x1 = 0;
            y1 = y1 + 1;
        }
        if (((unsigned int)img->image[counter]) != 0xffffffff)
            put_pixel(x1 + x, y1 + y, img->image[counter] >> 8 & 0x00FFFFFF, win);
        x1++;
        counter++;
    }
}

void draw_button(t_window *win, t_cub3_image *img, int x, int y)
{
    int x1;
    int y1;
    int counter;

    x1 = 0;
    y1 = 0;
    counter = 0;
    while (counter < img->height * img->width)
    {
        if (counter != 0 && counter % (img->width / 2) == 0)
        {
            x1 = 0;
            y1 = y1 + 1;
            counter += img->width / 2;
        }
        if (((unsigned int)img->image[counter]) != 0xffffffff)
            put_pixel(x1 + x, y1 + y, img->image[counter], win);
        x1++;
        counter++;
    }
}

void draw_button_hover(t_window *win, t_cub3_image *img, int x, int y)
{
    int x1;
    int y1;
    int counter;

    x1 = 0;
    y1 = 0;
    counter = 0;
    while (counter < img->height * img->width)
    {
        if (counter != 0 && counter % (img->width / 2) == 0)
        {
            x1 = 0;
            y1 = y1 + 1;
            counter += img->width / 2;
        }
        if (((unsigned int)img->image[counter]) != 0xffffffff)
            put_pixel(x1 + x, y1 + y, img->image[counter + img->width / 2], win);
        x1++;
        counter++;
    }
}

void draw_column(t_draw_pkg *pkg, int x, t_window *win)
{
    double step;
    double image_x;
    int image_y;
    int color;
    int y_counter;
        
    step = (double)pkg->image->height / (double)pkg->height;
    image_x = 0;
    y_counter = pkg->start - 1;
    while (++y_counter <= pkg->end)
    {
        image_y = (int)image_x;
        if (image_y >= pkg->image->height)
            image_y = pkg->image->height - 1;
        color = pkg->image->image[image_y * pkg->image->width + pkg->col];
        if ((unsigned int)color != 0xffffffff)
        {
            color = (color >> 8) & 0x00FFFFFF;
            put_pixel(x, y_counter, color, win);
        }
        image_x += step;
    }
}

void draw_image_rotated(t_window *win, t_cub3_image *img, int x, int y, double angle_deg)
{
    int dst_x, dst_y;
    double angle_rad;
    double cos_a, sin_a;
    double center_x, center_y;
    double src_x_f, src_y_f;
    int src_x, src_y;

    // Açıyı radyana çevir
    angle_rad = angle_deg * M_PI / 180.0;
    cos_a = cos(angle_rad);
    sin_a = sin(angle_rad);

    // Image merkezini hesapla
    center_x = img->width / 2.0;
    center_y = img->height / 2.0;

    // Her destination pixel için
    dst_y = 0;
    while (dst_y < img->height)
    {
        dst_x = 0;
        while (dst_x < img->width)
        {
            // Reverse rotation: bu destination pixel'in source'taki karşılığını bul
            src_x_f = cos_a * (dst_x - center_x) + sin_a * (dst_y - center_y) + center_x;
            src_y_f = -sin_a * (dst_x - center_x) + cos_a * (dst_y - center_y) + center_y;

            src_x = (int)(src_x_f + 0.5); // Round to nearest
            src_y = (int)(src_y_f + 0.5);

            // Bounds check
            if (src_x >= 0 && src_x < img->width && src_y >= 0 && src_y < img->height)
            {
                int src_idx = src_y * img->width + src_x;
                // Transparent pixel check (0xffffffff = transparent)
                if (((unsigned int)img->image[src_idx]) != 0xffffffff)
                    put_pixel(dst_x + x, dst_y + y, img->image[src_idx], win);
            }
            dst_x++;
        }
        dst_y++;
    }
} // claude

