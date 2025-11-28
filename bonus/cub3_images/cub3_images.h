/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3_images.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:11:18 by root              #+#    #+#             */
/*   Updated: 2025/11/28 03:21:35 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3_IMAGES_H
# define CUB3_IMAGES_H
# define BUFFER_SIZE 84
# define BIT_PER_PIXEL 3
# define RGB_FORMAT "RGB888"
# define CONTINUE 0
# define RESET 1

# include <fcntl.h>

typedef struct s_cub3_image			t_cub3_image;
typedef struct s_minimap_gallery	t_mmap_gallery;
typedef struct s_cub3_gallery		t_cub3_gallery;
typedef struct s_window				t_window;
typedef struct s_draw_pkg			t_draw_pkg;

typedef t_cub3_image				t_im;

struct								s_cub3_image
{
	int								*image;
	int								width;
	int								height;
};

# include "cub3_galleries.h"

struct								s_animated_sprite
{
	t_im							*frames;
	int								max_frame;
	int								curr_frame;
};

struct								s_cub3_gallery
{
	t_mmap_gal						mmap;
	t_frame_gal						frames;
	t_font_gal						fonts;
	t_mmenu_gal						menu;
	t_hud_gal						hud;
	t_shop_gal						shop;
	t_effect_gal					effect;
	t_enemy_gal						enemy;
	t_fireball_gal					fireball;
	t_misc_gal						misc;
	t_menus_bg_gal					menu_bg;
};

struct								s_draw_pkg
{
	t_im							*image;
	t_window						*window;
	int								height;
	int								start;
	int								end;
	int								col;
};

t_cub3_image	create_image(char *path);
void								draw_image(t_window *win, t_cub3_image *img,
										int x, int y);
void								draw_image_scaled(t_window *win,
										t_cub3_image *img, int x, int y,
										double scale);
void								draw_image_no_alpha(t_window *win,
										t_cub3_image *img, int x, int y);
void								draw_image_no_alpha_scaled(t_window *win,
										t_cub3_image *img, int x, int y,
										double scale);
void								draw_button(t_window *win,
										t_cub3_image *img, int x, int y);
void								draw_button_hover(t_window *win,
										t_cub3_image *img, int x, int y);
void								draw_column(t_draw_pkg *pkg, int x,
										t_window *win);
int									blend_alpha(int color, int color_to_blend,
										double alpha);
void								draw_column_alpha(t_draw_pkg *pkg, int x,
										t_window *win, int blend, double alpha);
void								*init_gallery_with_config(t_cub3_gallery *gal);

// Gallery init functions
void								init_enemy_gallery(t_cub3_gallery *gal);
void								init_fireball_gallery(t_cub3_gallery *gal);
void								init_frame_gallery(t_cub3_gallery *gal);
void								init_font_gallery(t_cub3_gallery *gal);
void								init_mmap_gallery(t_cub3_gallery *gal);
void								init_mmenu_gallery(t_cub3_gallery *gal);
void								init_hud_gallery(t_cub3_gallery *gal);
void								init_shop_gallery(t_cub3_gallery *gal);
void								init_effect_gallery(t_cub3_gallery *gal);
void								init_misc_gallery(t_cub3_gallery *gal);
void	init_menu_bg_gallery(t_cub3_gallery *gal);

#endif