/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3_galleries.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 22:25:41 by root              #+#    #+#             */
/*   Updated: 2025/11/29 22:03:58 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3_GALLERIES_H
# define CUB3_GALLERIES_H

# include "cub3_image_struct.h"

typedef struct s_minimap_gallery	t_mmap_gal;
typedef struct s_main_menu_gallery	t_mmenu_gal;
typedef struct s_hud_gallery		t_hud_gal;
typedef struct s_shop_gallery		t_shop_gal;
typedef struct s_effect_gallery		t_effect_gal;
typedef struct s_frame_gallery		t_frame_gal;
typedef struct s_font_gallery		t_font_gal;
typedef struct s_enemy_gallery		t_enemy_gal;
typedef struct s_fireball_gallery	t_fireball_gal;
typedef struct s_misc_gallery		t_misc_gal;
typedef struct s_menus_bg_gallery	t_menus_bg_gal;

struct s_minimap_gallery
{
	t_im	floor;
	t_im	wall;
	t_im	player;
	t_im	floor_void;
};

struct s_menus_bg_gallery
{
	t_im	main;
	t_im	pause;
	t_im	shop;
	t_im	map_select;
	t_im	summary;
	t_im	error;
};

struct s_main_menu_gallery
{
	t_im	start_btn;
	t_im	campaign_btn;
	t_im	continue_btn;
	t_im	maps_btn;
	t_im	exit_btn;
};

struct s_hud_gallery
{
	t_im	minimap;
	t_im	health_bar;
	t_im	mana_bar;
	t_im	currency;
	t_im	kill_counter;
};

struct s_shop_gallery
{
	t_im	adrenaline_potion;
	t_im	damage_increase;
	t_im	mana_increase;
	t_im	currency;
	t_im	buy_btn;
};

struct s_effect_gallery
{
	t_im	coin;
	t_im	damage;
};

struct s_frame_gallery
{
	t_im	low_hp_1;
	t_im	low_hp_2;
	t_im	low_hp_3;
};

struct s_font_gallery
{
	t_im	alagard;
};

struct s_enemy_gallery
{
	t_im	enemy1;
	t_im	enemy2;
	t_im	enemy3;
	t_im	enemy4;
	t_im	enemy5;
	t_im	enemy6;
	t_im	enemy7;
	t_im	enemy8;
	t_im	enemy9;
	t_im	enemy10;
	t_im	enemy11;
	t_im	enemy12;
	t_im	enemy13;
	t_im	enemy14;
};

struct								s_fireball_gallery
{
	t_im	fireball;
	t_im	fireball2;
	t_im	fireball3;
	t_im	fireball4;
	t_im	particle_1;
	t_im	particle_2;
	t_im	particle_3;
};

struct								s_misc_gallery
{
	t_im	cross;
	t_im	pokeball;
	t_im	currency;
	t_im	potion;
	t_im	healing_fx;
};

#endif
