/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 06:39:23 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/29 21:54:37 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../garbage_collector/garbage_collector.h"
# include "../map/map.h"
# include "../player/player.h"
# include "window.h"
# include "../render/render.h"
# include "../render/ray_list/render_ray_list.h"
# include "../hud/hud.h"
# include "../cub3_images/cub3_images.h"
# include "../cub3_fonts/cub3_fonts.h"
# include "../spellbook/bonus_spellbook.h"
# include "../objects/objects.h"
# include <stdbool.h>
# include "../sound/sound.h"
# include "../events/events.h"

# define MAP_TIME 1000

typedef struct s_main		t_main;
typedef struct s_record		t_record;
typedef enum e_game_state	t_game_state;

enum e_game_state
{
	MENU_MAIN = 0,
	GAME,
	MENU_PAUSE,
	MENU_MAP_SELECT,
	MENU_SHOP,
	MENU_ERROR,
	MENU_SUMMARY
};

struct s_record
{
	long long		play_time;
	unsigned int	kill_count;
	unsigned int	fireballs_cast;
	unsigned int	total_income;
	unsigned int	purchase_count;
};

struct s_main
{
	t_game_state	state;
	t_map			map;
	t_window		window;
	t_ray_list		rays;
	t_obj_list		objects;
	t_spellbook		spellbook;
	t_key_list		key_list;
	t_cub3_gallery	gallery;
	t_main_menu		main_menu;
	t_map_select	map_select;
	t_error			error_menu;
	t_shop			shop_menu;
	t_game_summary	summary_menu;
	t_font_menu		font_menu;
	t_cub3_image	minimap_full;
	t_record		record;
};

void		__init__(t_main *game);
void		_init_hooks(t_main *game);
void		center_window(t_main *g);
long long	current_time_ms(void);

#endif