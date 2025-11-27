/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemy_gallery.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 03:15:00 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/27 18:56:17 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_images.h"

void init_enemy_gallery(t_cub3_gallery *gal)
{
	gal->enemy.enemy1 = create_image("cub3_images/images/enemy/enemy1.cub3");
	gal->enemy.enemy2 = create_image("cub3_images/images/enemy/enemy2.cub3");
	gal->enemy.enemy3 = create_image("cub3_images/images/enemy/enemy3.cub3");
	gal->enemy.enemy4 = create_image("cub3_images/images/enemy/enemy4.cub3");
	gal->enemy.enemy5 = create_image("cub3_images/images/enemy/enemy5.cub3");
	gal->enemy.enemy6 = create_image("cub3_images/images/enemy/enemy6.cub3");
	gal->enemy.enemy7 = create_image("cub3_images/images/enemy/enemy7.cub3");
	gal->enemy.enemy8 = create_image("cub3_images/images/enemy/enemy8.cub3");
	gal->enemy.enemy9 = create_image("cub3_images/images/enemy/enemy9.cub3");
	gal->enemy.enemy10 = create_image("cub3_images/images/enemy/enemy10.cub3");
	gal->enemy.enemy11 = create_image("cub3_images/images/enemy/enemy11.cub3");
	gal->enemy.enemy12 = create_image("cub3_images/images/enemy/enemy12.cub3");
	gal->enemy.enemy13 = create_image("cub3_images/images/orb/pokeball.cub3");
	gal->enemy.enemy14 = create_image("cub3_images/images/orb/pokeball.cub3");
}
