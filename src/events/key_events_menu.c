/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events_menu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 07:17:25 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 21:21:29 by btuncer          ###   ########.fr       */
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
