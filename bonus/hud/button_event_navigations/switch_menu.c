/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 23:12:39 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/22 05:33:44 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"

void	switch_menu(t_main *g)
{
	if (g->state == MENU_PAUSE || g->state == MENU_MAIN)
	{
		g->state = GAME;
		mlx_mouse_hide(g->window.mlx, g->window.win);
	}
	else if (g->state == GAME)
	{
		g->state = MENU_PAUSE;
		mlx_mouse_show(g->window.mlx, g->window.win);
	}
	else if (g->state == MENU_MAP_SELECT)
		g->state = GAME;
	system(AUDIO_MAIN_MENU);
}
