/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 05:39:18 by root              #+#    #+#             */
/*   Updated: 2025/11/27 18:57:58 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	draw_image(t_window *win, t_cub3_image *img, int x, int y)
{
	int	x1;
	int	y1;
	int	counter;

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

static void	draw_scaled_pixel(t_window *win, t_cub3_image *img,
		t_vector_int offset, t_vector_int dst, double scale)
{
	t_vector_int	src;
	int				color;

	src.x = (int)(dst.x / scale);
	src.y = (int)(dst.y / scale);
	if (src.x < img->width && src.y < img->height)
	{
		color = img->image[src.y * img->width + src.x];
		if ((unsigned int)color != 0xffffffff)
			put_pixel(offset.x + dst.x, offset.y + dst.y, color, win);
	}
}

void	draw_image_scaled(t_window *win, t_cub3_image *img, int x, int y,
		double scale)
{
	t_vector_int	offset;
	t_vector_int	dst;
	t_vector_int	size;

	size.x = (int)(img->width * scale);
	size.y = (int)(img->height * scale);
	offset.x = x;
	offset.y = y;
	dst.y = 0;
	while (dst.y < size.y)
	{
		dst.x = 0;
		while (dst.x < size.x)
		{
			draw_scaled_pixel(win, img, offset, dst, scale);
			dst.x++;
		}
		dst.y++;
	}
}

void	draw_column(t_draw_pkg *pkg, int x, t_window *win)
{
	double	step;
	double	image_x;
	int		image_y;
	int		color;
	int		y_counter;

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
