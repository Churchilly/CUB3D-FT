/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_select.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 03:32:58 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/16 05:10:13 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud.h"

void	next_button(t_main_menu *menu)
{
	if (!menu->active)
		return ;
	if (menu->selected == &menu->btn_start)
		menu->selected = &menu->btn_exit;
	else if (menu->selected == &menu->btn_exit)
		menu->selected = &menu->btn_start;
}

void	prev_button(t_main_menu *menu)
{
	if (!menu->active)
		return ;
	if (menu->selected == &menu->btn_start)
		menu->selected = &menu->btn_exit;
	else if (menu->selected == &menu->btn_exit)
		menu->selected = &menu->btn_start;
}