/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_select.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 03:32:58 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/16 07:38:38 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud.h"

void	next_button(t_main_menu *menu)
{
	if (!menu->active)
		return ;
	if (menu->selected == &menu->btn_campaign)
		menu->selected = &menu->btn_map_selector;
	else if (menu->selected == &menu->btn_exit)
	{
		if (menu->btn_continue.height != -1)
			menu->selected = &menu->btn_continue;
		else
			menu->selected = &menu->btn_campaign;
	}
	else if (menu->selected == &menu->btn_map_selector)
		menu->selected = &menu->btn_exit;
	else if (menu->selected == &menu->btn_continue)
		menu->selected = &menu->btn_campaign;
}

void	prev_button(t_main_menu *menu)
{
	if (!menu->active)
		return ;
	if (menu->selected == &menu->btn_campaign)
	{
		if (menu->btn_continue.height != -1)
			menu->selected = &menu->btn_continue;
		else
			menu->selected = &menu->btn_exit;
	}
	else if (menu->selected == &menu->btn_exit)
		menu->selected = &menu->btn_map_selector;
	else if (menu->selected == &menu->btn_map_selector)
		menu->selected = &menu->btn_campaign;
	else if (menu->selected == &menu->btn_continue)
		menu->selected = &menu->btn_exit;
}