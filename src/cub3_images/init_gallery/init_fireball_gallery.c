/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fireball_gallery.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 03:15:00 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/28 17:50:40 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_images.h"

void	init_fireball_gallery(t_cub3_gallery *gal)
{
	gal->fireball.fireball \
		= create_image("cub3_images/images/fireball/firbal.cub3");
	gal->fireball.fireball2 \
		= create_image("cub3_images/images/fireball/firbal_2.cub3");
	gal->fireball.fireball3 \
		= create_image("cub3_images/images/fireball/firbal_3.cub3");
	gal->fireball.fireball4 \
		= create_image("cub3_images/images/fireball/firbal_2.cub3");
	gal->fireball.particle_1 \
		= create_image("cub3_images/images/fireball/fireball_particle_1.cub3");
	gal->fireball.particle_2 \
		= create_image("cub3_images/images/fireball/fireball_particle_2.cub3");
	gal->fireball.particle_3 \
		= create_image("cub3_images/images/fireball/fireball_particle_3.cub3");
}
