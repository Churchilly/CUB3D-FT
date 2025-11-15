/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3_galleries.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 22:25:41 by root              #+#    #+#             */
/*   Updated: 2025/11/15 22:54:13 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3_GALLERIES_H
# define CUB3_GALLERIES_H

typedef t_im;
typedef struct s_number_gallery t_num_gal;
typedef struct s_minimap_gallery t_mmap_gal;
typedef struct s_main_menu_gallery t_mmenu_gal;
typedef struct s_hud_gallery t_hud_gal;
typedef struct s_shop_gallery t_shop_gal;
typedef struct s_effect_gallery t_effect_gal;

struct s_number_gallery
{
    t_im num_0;
    t_im num_1;
    t_im num_2;
    t_im num_3;
    t_im num_4;
    t_im num_5;
    t_im num_6;
    t_im num_7;
    t_im num_8;
    t_im num_9;
    t_im num_dot;
};

struct s_minimap_gallery
{
    t_im floor;
    t_im wall;
    t_im player;
    t_im floor_void;
};

struct s_main_menu_gallery
{
    t_im bg;
    t_im bg_active;
    t_im start_btn;
    t_im campaign_btn;
    t_im maps_btn;
    t_im exit_btn;
};

struct s_hud_gallery
{
    t_im minimap;
    t_im health_bar;
    t_im mana_bar;
    t_im currency;
    t_im kill_counter;
};

struct s_shop_gallery
{
    t_im adrenaline_potion;
    t_im damage_increase;
    t_im mana_increase;
    t_im currency;
    t_im buy_btn;
};

struct s_effect_gallery
{
    t_im coin;
    t_im damage;
};

#endif