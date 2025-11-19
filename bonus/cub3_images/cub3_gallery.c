/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3_gallery.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 00:00:59 by root              #+#    #+#             */
/*   Updated: 2025/11/20 01:07:55 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3_images.h"

static void init_mmap_gallery(t_cub3_gallery *gal)
{
    gal->mmap.floor = create_image("cub3_images/images/minimap/floor.cub3");
    gal->mmap.wall = create_image("cub3_images/images/minimap/wall.cub3");
    gal->mmap.player = create_image("cub3_images/images/minimap/player.cub3");
    gal->mmap.floor_void = create_image("cub3_images/images/minimap/floor_void.cub3");
}

void *init_gallery_with_config(t_cub3_gallery *gal, char *config)
{
    t_cub3_image img = create_image("cub3_images/images/main_menu.cub3");
    t_cub3_image img2 = create_image("cub3_images/images/main_menu_active.cub3");
    t_cub3_image img3 = create_image("cub3_images/images/main_menu_start_btn.cub3");

    (void)config;
    gal->mmenu_bg = img;
    gal->mmenu_bg_active = create_image("cub3_images/images/qwer.cub3");
    gal->mmenu_start_btn = img3;
    gal->fireball = create_image("cub3_images/images/fireball/firbal.cub3");
    gal->fireball2 = create_image("cub3_images/images/fireball/firbal_2.cub3");
    gal->fireball3 = create_image("cub3_images/images/fireball/firbal_3.cub3");
    gal->fireball4 = create_image("cub3_images/images/fireball/firbal_2.cub3");
    gal->fireball_particle_1 = create_image("cub3_images/images/fireball/fireball_particle_1.cub3");
    gal->fireball_particle_2 = create_image("cub3_images/images/fireball/fireball_particle_2.cub3");
    gal->fireball_particle_3 = create_image("cub3_images/images/fireball/fireball_particle_3.cub3");
    gal->cross = create_image("cub3_images/images/crosshair.cub3");
    gal->frames.low_hp_1 = create_image("cub3_images/images/frames/low_hp_frame.cub3");
    gal->frames.low_hp_2 = create_image("cub3_images/images/frames/low_hp_frame_2.cub3");
    gal->frames.low_hp_3 = create_image("cub3_images/images/frames/low_hp_frame_3.cub3");
	gal->enemy1 = create_image("cub3_images/images/enemy/enemy1.cub3");
	gal->enemy2 = create_image("cub3_images/images/enemy/enemy2.cub3");
	gal->enemy3 = create_image("cub3_images/images/enemy/enemy3.cub3");
	gal->enemy4 = create_image("cub3_images/images/enemy/enemy4.cub3");
	gal->enemy5 = create_image("cub3_images/images/enemy/enemy5.cub3");
	gal->enemy6 = create_image("cub3_images/images/enemy/enemy6.cub3");
	gal->enemy7 = create_image("cub3_images/images/enemy/enemy7.cub3");
	gal->enemy8 = create_image("cub3_images/images/enemy/enemy8.cub3");
	gal->enemy9 = create_image("cub3_images/images/enemy/enemy9.cub3");
	gal->enemy10 = create_image("cub3_images/images/enemy/enemy10.cub3");
	gal->enemy11 = create_image("cub3_images/images/enemy/enemy11.cub3");
	gal->enemy12 = create_image("cub3_images/images/enemy/enemy12.cub3");
    gal->fonts.alagard = create_image("cub3_images/images/fonts/alagard.cub3");
    gal->pokeball = create_image("cub3_images/images/orb/pokeball.cub3");
    gal->currency = create_image("cub3_images/images/player/coin.cub3");
    gal->potion = create_image("cub3_images/images/player/potion.cub3");
    init_mmap_gallery(gal);
    return (gal);
} // this is OK for TODO#1, not for the other
