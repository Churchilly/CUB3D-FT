/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3_images.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:11:18 by root              #+#    #+#             */
/*   Updated: 2025/11/19 01:59:15 by yusudemi         ###   ########.fr       */
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
# include "../gc/gc.h"

typedef struct s_cub3_image t_cub3_image;
typedef struct s_minimap_gallery t_mmap_gallery;
typedef struct s_cub3_gallery t_cub3_gallery;
typedef struct s_window t_window;
typedef struct s_draw_pkg t_draw_pkg;

typedef t_cub3_image t_im;

struct s_cub3_image
{
    int *image;
    int width;
    int height;
};

# include "cub3_galleries.h"

struct s_animated_sprite
{
    t_im *frames;
    int max_frame;
    int curr_frame;
};

struct s_cub3_gallery
{
    t_im mmenu_bg;
    t_im mmenu_bg_active;
    t_im mmenu_start_btn;
    t_im fireball;
    t_im fireball2;
    t_im fireball3;
    t_im fireball4;
    t_im fireball_particle_1;
    t_im fireball_particle_2;
    t_im fireball_particle_3;
    t_im cross;
    t_mmap_gal mmap;
    t_frame_gal frames;
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

struct s_draw_pkg
{
    t_im *image;
    t_window *window;
    int height;
    int start;
    int end;
    int col;
};

t_cub3_image create_image(char *path);
void draw_image(t_window *win, t_cub3_image *img, int x, int y);
void draw_image_no_alpha(t_window *win, t_cub3_image *img, int x, int y);
void draw_image_rotated(t_window *win, t_cub3_image *img, int x, int y, double angle_deg); // claude
void draw_button(t_window *win, t_cub3_image *img, int x, int y);
void draw_button_hover(t_window *win, t_cub3_image *img, int x, int y);
void draw_column(t_draw_pkg *pkg, int x, t_window *win);
void *init_gallery_with_config(t_cub3_gallery *gal, char *config);

#endif