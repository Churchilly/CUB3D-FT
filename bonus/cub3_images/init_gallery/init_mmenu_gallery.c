/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mmenu_gallery.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 03:15:00 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/24 15:29:23 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_images.h"

void	init_mmenu_gallery(t_cub3_gallery *gal)
{
	gal->menu.bg = create_image("cub3_images/images/main_menu.cub3");
	gal->menu.bg_active = create_image("cub3_images/images/orb/pokeball.cub3");
	gal->menu.start_btn = create_image("cub3_images/images/main_menu_start_btn.cub3");
	gal->menu.campaign_btn = create_image("cub3_images/images/buttons/btn_campaign.cub3");
	gal->menu.continue_btn = create_image("cub3_images/images/buttons/btn_continue.cub3");
	gal->menu.maps_btn = create_image("cub3_images/images/buttons/btn_maps.cub3");
	gal->menu.exit_btn = create_image("cub3_images/images/buttons/btn_exit.cub3");
}
