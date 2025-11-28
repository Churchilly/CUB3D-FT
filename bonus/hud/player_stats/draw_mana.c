/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mana.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:54:19 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/28 17:34:57 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

static void	draw_line_of_mana(t_main *g, int vol)
{
	int	counter;
	int	color;

	if (g->map.player.mana <= MANA_CRIT_VAL)
		color = CRIT_STAT_COLOR;
	else
		color = MANA_COLOR;
	counter = 20;
	while (counter--)
		put_pixel(vol, MANA_POS_Y + counter, color, &g->window);
}

void	draw_mana_bar(t_main *g)
{
	int	counter;

	counter = (int)g->map.player.mana;
	while (counter--)
	{
		draw_line_of_mana(g, MANA_POS_X + counter);
	}
}
