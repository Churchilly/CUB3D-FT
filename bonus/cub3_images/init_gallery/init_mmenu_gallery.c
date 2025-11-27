/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mmenu_gallery.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 03:15:00 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/27 18:57:10 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_images.h"

void	init_mmenu_gallery(t_cub3_gallery *gal)
{
	gal->menu.start_btn = create_image("cub3_images/images/main_menu_start_btn.cub3");
	gal->menu.campaign_btn = create_image("cub3_images/images/buttons/btn_campaign.cub3");
	gal->menu.continue_btn = create_image("cub3_images/images/buttons/btn_continue.cub3");
	gal->menu.maps_btn = create_image("cub3_images/images/buttons/btn_maps.cub3");
	gal->menu.exit_btn = create_image("cub3_images/images/buttons/btn_exit.cub3");
}
