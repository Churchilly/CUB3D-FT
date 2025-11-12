/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_health.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:54:19 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/12 19:42:01 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

static void draw_line_of_health(t_main *g, int vol)
{
    int counter;
    
    counter = 20;
    while (counter--)
    {
        put_pixel(vol, HEALTH_POS_Y + counter, HEALTH_COLOR, &g->window);
    }
}

void draw_heath_bar(t_main *g)
{
    int counter;

    counter = (int)g->map.player.health;
    while (counter--)
    {
        draw_line_of_health(g, HEALTH_POS_X + counter);
    }
}
