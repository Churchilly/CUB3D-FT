/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3_gallery.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 00:00:59 by root              #+#    #+#             */
/*   Updated: 2025/11/26 20:14:00 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3_images.h"

void *init_gallery_with_config(t_cub3_gallery *gal)
{
	init_enemy_gallery(gal);
	init_fireball_gallery(gal);
	init_frame_gallery(gal);
	init_font_gallery(gal);
	init_mmap_gallery(gal);
	init_mmenu_gallery(gal);
	init_hud_gallery(gal);
	init_shop_gallery(gal);
	init_effect_gallery(gal);
	init_misc_gallery(gal);
	init_menu_bg_gallery(gal);
	return (gal);
}
