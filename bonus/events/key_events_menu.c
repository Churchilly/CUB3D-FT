/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events_menu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 07:17:25 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/24 07:25:36 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <X11/keysym.h>

void	onpress_event_menu(int key, t_main *game)
{
	if (key == XK_w)
		prev_button(game);
	else if (key == XK_s)
		next_button(game);
	else if (key == XK_space || key == XK_Return)
		activate_button(game);
	else if (key == XK_a && game->state == MENU_MAP_SELECT)
		prev_page(game);
	else if (key == XK_d && game->state == MENU_MAP_SELECT)
		next_page(game);
}
