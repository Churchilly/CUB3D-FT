/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_events_game.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 07:58:52 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 04:27:49 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

static void	update_play_time(t_main *g)
{
	static long long	timer = 0;
	long long			curr_time;

	curr_time = current_time_ms();
	if (curr_time - timer > 1000)
	{
		g->map.map_timer++;
		g->record.play_time++;
		timer = curr_time;
	}
}

static void	check_game_time(t_main *g)
{
	if (g->map.map_timer >= GAME_TIME)
	{
		if (g->map.next_map)
		{
			g->state = MENU_SHOP;
			g->shop_menu.selected = &g->shop_menu.items[0];
		}
		else
		{
			g->state = MENU_SUMMARY;
		}
	}
	if (g->map.player.health <= 0 && IMMORTALITY == 0)
		g->state = MENU_SUMMARY;
}

static void	update_game(t_main *g)
{
	update_play_time(g);
	check_game_time(g);
	change_position(g);
	change_direction(g);
	animate_objects(g);
	animate_spellbook(g);
	update_mana(g);
	update_health(g);
	draw_currency_game(g);
	if (g->key_list.f3.key_switch)
	{
		read_mouse_movements(g);
		center_mouse(g);
	}
}

void	render_screen(t_main *game)
{
	if (game->state == MENU_MAIN)
		render_main_menu(game);
	else if (game->state == MENU_PAUSE)
		render_pause_menu(game);
	else if (game->state == GAME)
	{
		render_game(game);
		update_game(game);
	}
	else if (game->state == MENU_MAP_SELECT)
		render_select_map(game);
	else if (game->state == MENU_SHOP)
		render_shop(game);
	else if (game->state == MENU_ERROR)
		render_error_menu(game);
	else if (game->state == MENU_SUMMARY)
		render_summary_menu(game);
}
