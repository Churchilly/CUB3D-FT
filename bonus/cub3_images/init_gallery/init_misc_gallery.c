/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_misc_gallery.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 03:15:00 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/28 17:49:12 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_images.h"

void	init_misc_gallery(t_cub3_gallery *gal)
{
	gal->misc.cross = create_image("cub3_images/images/crosshair.cub3");
	gal->misc.pokeball = create_image("cub3_images/images/orb/pokeball.cub3");
	gal->misc.currency = create_image("cub3_images/images/player/coin.cub3");
	gal->misc.potion = create_image("cub3_images/images/player/potion.cub3");
	gal->misc.healing_fx \
		= create_image("cub3_images/images/player/healing.cub3");
}
