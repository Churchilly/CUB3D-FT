/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_currency.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:54:19 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/28 17:27:49 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <stdlib.h>
#include <stdio.h>

void draw_currency_game(t_main *g)
{
    int currency;
    t_cub3_image *img;
    char text[16];

    currency = g->map.player.inventory.currency;
    img = &g->gallery.misc.currency;
    sprintf(text, "%d", currency);
    draw_image_no_alpha_scaled(&g->window, img, (t_pos){15, 280}, .045);
	draw_text(text,
		(t_text){16, 20 + img->width * .045, 292,
			&g->font_menu.alagard, 0, 0, .75, &g->window, GOLD_COLOR});
}