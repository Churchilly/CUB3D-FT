/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud_gallery.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 03:15:00 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/28 17:50:10 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_images.h"

void	init_hud_gallery(t_cub3_gallery *gal)
{
	gal->hud.minimap = create_image("cub3_images/images/orb/pokeball.cub3");
	gal->hud.health_bar = create_image("cub3_images/images/orb/pokeball.cub3");
	gal->hud.mana_bar = create_image("cub3_images/images/orb/pokeball.cub3");
	gal->hud.currency = create_image("cub3_images/images/player/coin.cub3");
	gal->hud.kill_counter \
		= create_image("cub3_images/images/orb/pokeball.cub3");
}
