/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shop_gallery.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 03:15:00 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/27 18:57:15 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_images.h"

void	init_shop_gallery(t_cub3_gallery *gal)
{
	gal->shop.adrenaline_potion = create_image("cub3_images/images/orb/pokeball.cub3");
	gal->shop.damage_increase = create_image("cub3_images/images/orb/pokeball.cub3");
	gal->shop.mana_increase = create_image("cub3_images/images/orb/pokeball.cub3");
	gal->shop.currency = create_image("cub3_images/images/player/coin.cub3");
	gal->shop.buy_btn = create_image("cub3_images/images/orb/pokeball.cub3");
}
