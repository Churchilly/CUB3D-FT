/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3_draw_button.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:28:37 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/27 18:57:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

void	draw_button(t_window *win, t_cub3_image *img, int x, int y)
{
	int	x1;
	int	y1;
	int	counter;

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
			put_pixel(x1 + x, y1 + y, img->image[counter] >> 8 & 0x00FFFFFF,
				win);
		x1++;
		counter++;
	}
}

void	draw_button_hover(t_window *win, t_cub3_image *img, int x, int y)
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
			put_pixel(x1 + x, y1 + y, img->image[counter + img->width
				/ 2] >> 8 & 0x00FFFFFF, win);
		x1++;
		counter++;
	}
}
