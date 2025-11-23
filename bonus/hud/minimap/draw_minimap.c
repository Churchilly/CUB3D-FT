/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 01:15:49 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/22 07:06:46 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hud.h"
#include "../../main/main.h"
#include <math.h>

static void	rotate_pixel(t_vector_int *src, t_vector_int dst,
	t_vector_int ctr, double angle)
{
	double	cos_a;
	double	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	src->x = (int)(cos_a * (dst.x - ctr.x) + sin_a * (dst.y - ctr.y)
			+ ctr.x + 0.5);
	src->y = (int)(-sin_a * (dst.x - ctr.x) + cos_a * (dst.y - ctr.y)
			+ ctr.y + 0.5);
}

static void	draw_cropped_rotated(t_main *g, t_cub3_image *img, int cx, int cy)
{
	t_vector_int	dst;
	t_vector_int	src;
	t_vector_int	ctr;
	int				dist_sq;
	int				r_sq;

	ctr = (t_vector_int){img->width / 2, img->height / 2};
	r_sq = (MMAP_RANGE * MMAP_GRID_SIZE) * (MMAP_RANGE * MMAP_GRID_SIZE);
	dst.y = -1;
	while (++dst.y < img->height)
	{
		dst.x = -1;
		while (++dst.x < img->width)
		{
			dist_sq = (dst.x - ctr.x) * (dst.x - ctr.x)
				+ (dst.y - ctr.y) * (dst.y - ctr.y);
			if (dist_sq > r_sq)
				continue ;
			rotate_pixel(&src, dst, ctr, -(g->map.player.dov + 1.5));
			if (src.x >= 0 && src.x < img->width && src.y >= 0
				&& src.y < img->height)
				put_pixel(cx + dst.x - ctr.x + MMAP_MARGIN, cy + dst.y - ctr.y + MMAP_MARGIN,
					img->image[src.y * img->width + src.x], &g->window);
		}
	}
}

static void	crop_minimap(t_main *g, t_cub3_image *cropped, int player_px, int player_py)
{
	int	src_x;
	int	src_y;
	int	dst_idx;
	int	radius;

	radius = MMAP_RANGE * MMAP_GRID_SIZE;
	dst_idx = 0;
	src_y = player_py - radius;
	while (src_y < player_py + radius)
	{
		src_x = player_px - radius;
		while (src_x < player_px + radius)
		{
			if (src_x >= 0 && src_x < g->minimap_full.width && src_y >= 0 && src_y < g->minimap_full.height)
				cropped->image[dst_idx] = g->minimap_full.image[src_y * g->minimap_full.width + src_x];
			else
				cropped->image[dst_idx] = 0xffffffff;
			dst_idx++;
			src_x++;
		}
		src_y++;
	}
}

void	draw_mmap(t_main *g)
{
	t_cub3_image	cropped;
	int				player_px;
	int				player_py;
	int				size;

	player_px = (int)(g->map.player.pos.x * MMAP_GRID_SIZE);
	player_py = (int)(g->map.player.pos.y * MMAP_GRID_SIZE);
	size = MMAP_RANGE * MMAP_GRID_SIZE * 2;
	cropped.width = size;
	cropped.height = size;
	cropped.image = alloc(size * size * sizeof(int), DYNAMIC);
	crop_minimap(g, &cropped, player_px, player_py);
	draw_cropped_rotated(g, &cropped, (MMAP_GRID_COUNT / 2 + 1) * MMAP_GRID_SIZE,
		(MMAP_GRID_COUNT / 2 + 1) * MMAP_GRID_SIZE);
	draw_image(&g->window, &g->gallery.mmap.player,
		(MMAP_GRID_COUNT / 2 + 1) * MMAP_GRID_SIZE - g->gallery.mmap.player.width / 2,
		(MMAP_GRID_COUNT / 2 + 1) * MMAP_GRID_SIZE - g->gallery.mmap.player.height / 2);
}
