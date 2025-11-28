/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_health.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:54:19 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/28 17:23:58 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

static void	draw_line_of_health(t_main *g, int vol)
{
	int	counter;
	int	color;

	if (g->map.player.health <= HEALTH_CRIT_VAL)
		color = CRIT_STAT_COLOR;
	else
		color = HEALTH_COLOR;
	counter = 20;
	while (counter--)
		put_pixel(vol, HEALTH_POS_Y + counter, color, &g->window);
}

void	draw_heath_bar(t_main *g)
{
	int	counter;

	counter = (int)g->map.player.health;
	while (counter--)
		draw_line_of_health(g, HEALTH_POS_X + counter);
}
