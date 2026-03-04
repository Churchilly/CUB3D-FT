/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3_draw_button.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:28:37 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/28 17:38:40 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	draw_button(t_window *win, t_cub3_image *img, int x, int y)
{
	int	x1;
	int	y1;
	int	counter;
	int	pixel_index;

	x1 = 0;
	y1 = 0;
	counter = 0;
	while (counter < img->height * (img->width / 2))
	{
		if (counter != 0 && counter % (img->width / 2) == 0)
		{
			x1 = 0;
			y1 = y1 + 1;
		}
		pixel_index = (counter / (img->width / 2)) * img->width + (counter
				% (img->width / 2));
		if (((unsigned int)img->image[pixel_index]) != 0xffffffff)
			put_pixel(x1 + x, y1 + y, img->image[pixel_index] >> 8 & 0x00FFFFFF,
				win);
		x1++;
		counter++;
	}
}

void	draw_button_hover(t_window *win, t_cub3_image *img, int x, int y)
{
	int	x1;
	int	y1;
	int	counter;
	int	pixel_index;

	x1 = 0;
	y1 = 0;
	counter = 0;
	while (counter < img->height * (img->width / 2))
	{
		if (counter != 0 && counter % (img->width / 2) == 0)
		{
			x1 = 0;
			y1 = y1 + 1;
		}
		pixel_index = (counter / (img->width / 2)) * img->width + (counter
				% (img->width / 2)) + (img->width / 2);
		if (((unsigned int)img->image[pixel_index]) != 0xffffffff)
			put_pixel(x1 + x, y1 + y, img->image[pixel_index] >> 8 & 0x00FFFFFF,
				win);
		x1++;
		counter++;
	}
}
