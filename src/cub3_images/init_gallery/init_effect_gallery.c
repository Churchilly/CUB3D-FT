/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_effect_gallery.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 03:15:00 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/28 17:41:09 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_images.h"

void	init_effect_gallery(t_cub3_gallery *gal)
{
	gal->effect.coin = create_image("cub3_images/images/player/coin.cub3");
	gal->effect.damage = create_image("cub3_images/images/orb/pokeball.cub3");
}
