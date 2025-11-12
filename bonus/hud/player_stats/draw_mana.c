/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mana.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:54:19 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/12 19:36:10 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

// 
// void	put_pixel(int x, int y, int color, t_window *win);

static void draw_line_of_mana(t_main *g, int vol)
{
    int counter;
    
    counter = 20;
    while (counter--)
    {
        put_pixel(vol, MANA_POS_Y + counter, MANA_COLOR, &g->window);
    }
}

void draw_mana_bar(t_main *g)
{
    int counter;

    counter = (int)g->map.player.mana;
    while (counter--)
    {
        draw_line_of_mana(g, MANA_POS_X + counter);
    }
}
