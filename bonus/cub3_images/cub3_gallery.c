/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3_gallery.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 00:00:59 by root              #+#    #+#             */
/*   Updated: 2025/11/12 16:10:32 by btuncer          ###   ########.fr       */
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
    gal->mmenu_bg_active = img2;
    gal->mmenu_start_btn = img3;
    init_mmap_gallery(gal);
    return (gal);
} // this is OK for TODO#1, not for the other
