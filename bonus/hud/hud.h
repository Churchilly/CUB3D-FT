/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:51:08 by root              #+#    #+#             */
/*   Updated: 2025/11/16 07:13:09 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUD_H
# define HUD_H

// MINIMAP DEFINES
# define MMAP_GRID_SIZE 20
# define MMAP_GRID_COUNT 9
# define MMAP_RANGE 7
# define MMAP_MARGIN 20

# define MMAP_PLAYER_IMAGE_OFFSET 90.0

// PLAYER STATS DEFINES
# define MANA_COLOR 0xff2757f5
# define MANA_POS_X 20
# define MANA_POS_Y 227
# define MANA_CRIT_VAL 40.0
# define MAX_MANA 150.0

# define HEALTH_COLOR 0xffff2424
# define HEALTH_POS_X 20
# define HEALTH_POS_Y 205
# define HEALTH_CRIT_VAL 50.0
# define MAX_HEALTH 175.0

# define CRIT_STAT_COLOR 0xff502370

# include "../minilibx/mlx.h"
# include "../cub3_images/cub3_images.h"
# include "../main/vector.h"
# include <stdbool.h>

typedef struct s_button		t_button;
typedef struct s_main_menu	t_main_menu;
typedef struct s_main		t_main;
typedef struct s_pos		t_pos;
typedef enum e_button_type	t_button_type;

enum e_button_type
{
	BUTTON_START,
	BUTTON_EXIT	
};

struct s_button
{
	t_im		image;
	t_vector	position;
	int			width;
	int			height;
};

struct s_main_menu
{
	bool			active;
	t_button		*selected;
	t_cub3_image	bg_img;
	t_button		btn_continue;
	t_button		btn_campaign;
	t_button		btn_map_selector;
	t_button		btn_exit;
};

struct s_map_selector
{
	bool			active;
	t_button		*selected;
	t_cub3_image	bg_img;
	t_button		btn_maps[5];
};

struct s_pos
{
	int	x;
	int	y;
};

void	draw_minimap(t_main *game);
void	draw_mmap(t_main *g);

void	*init_main_menu(t_main *g, t_main_menu *mmenu);
void	switch_main_menu(t_main *g);

void	*set_button(t_button *button, t_im *img, t_vector pos);
void	check_button(t_main *game, t_button *button);
void	place_button(t_main *g, t_button *btn);
void	activate_button(t_main *g);
//bool is_xy_on_button(int x, int y, t_button *btn);

void	next_button(t_main_menu *menu);
void	prev_button(t_main_menu *menu);

void	draw_mana_bar(t_main *g);
void	draw_heath_bar(t_main *g);

#endif