/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_frame_gallery.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 03:15:00 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/28 17:50:24 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_images.h"

void	init_frame_gallery(t_cub3_gallery *gal)
{
	gal->frames.low_hp_1 \
		= create_image("cub3_images/images/frames/low_hp_frame.cub3");
	gal->frames.low_hp_2 \
		= create_image("cub3_images/images/frames/low_hp_frame_2.cub3");
	gal->frames.low_hp_3 \
		= create_image("cub3_images/images/frames/low_hp_frame_3.cub3");
}
