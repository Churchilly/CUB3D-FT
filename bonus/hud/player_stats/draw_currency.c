/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_currency.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:54:19 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/20 01:30:37 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <stdlib.h>

void draw_currency(t_main *g)
{
    int currency;

    currency = g->map.player.inventory.currency;
    draw_image_no_alpha_scaled(&g->window, &g->gallery.currency, 580, 10, 0.08);
    draw_text(ft_itoa(currency), &g->font_menu.alagard, (t_pos){590, 10}, &g->window, 1);
}