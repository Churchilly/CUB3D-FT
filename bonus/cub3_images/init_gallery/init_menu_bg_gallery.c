/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu_bg_gallery.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:14:21 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/27 18:56:45 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_images.h"

void	init_menu_bg_gallery(t_cub3_gallery *gal)
{
	gal->menu_bg.main = create_image("cub3_images/images/menus/mmenu_bg.cub3");
	gal->menu_bg.pause = create_image("cub3_images/images/menus/pause_menu_bg.cub3");
	gal->menu_bg.shop = create_image("cub3_images/images/menus/shop_bg.cub3");
	gal->menu_bg.map_select = create_image("cub3_images/images/menus/map_select_bg.cub3");
	gal->menu_bg.summary = create_image("cub3_images/images/menus/pause_menu_bg.cub3");
	gal->menu_bg.error = create_image("cub3_images/images/menus/pause_menu_bg.cub3");
}
