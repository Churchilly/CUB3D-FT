/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_font_gallery.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 03:15:00 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/24 03:15:00 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_images.h"

void	init_font_gallery(t_cub3_gallery *gal)
{
	gal->fonts.alagard = create_image("cub3_images/images/fonts/alagard.cub3");
}
