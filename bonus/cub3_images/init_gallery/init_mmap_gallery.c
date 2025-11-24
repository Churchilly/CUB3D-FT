/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mmap_gallery.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 03:15:00 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/24 03:15:00 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_images.h"

void	init_mmap_gallery(t_cub3_gallery *gal)
{
	gal->mmap.floor = create_image("cub3_images/images/minimap/floor.cub3");
	gal->mmap.wall = create_image("cub3_images/images/minimap/wall.cub3");
	gal->mmap.player = create_image("cub3_images/images/minimap/player.cub3");
	gal->mmap.floor_void = create_image("cub3_images/images/minimap/floor_void.cub3");
}
