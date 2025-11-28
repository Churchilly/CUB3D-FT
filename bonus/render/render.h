/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:02:04 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/28 22:33:12 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../player/player.h"
# include "../map/map.h"

typedef struct s_ray				t_ray;
typedef struct s_main				t_main;
typedef struct s_window				t_window;
typedef struct s_object_node		t_obj_node;
typedef struct s_orb				t_orb;
typedef struct s_door				t_door;
typedef struct s_enemy				t_enemy;
typedef struct s_fireball			t_fireball;
typedef struct s_fireball_particle	t_fire_particle;
typedef struct s_cub3_image			t_cub3_image;
typedef t_cub3_image				t_im;
typedef struct s_ray_list			t_ray_list;

typedef struct s_render_floor_data	t_render_floor_data;
typedef struct s_cast_data			t_cast_data;
typedef struct s_render_wall_data	t_render_wall_data;

struct s_cast_data
{
	t_ray			*ray;
	t_player		*player;
	t_vector_int	map_pos;
	t_vector		ray_d;
	t_vector_int	step;
	t_vector		side_dist;
	t_vector		delta_dist;
	double			fov_rad;
	double			direction;
	void			*door_walls;
};

struct s_render_wall_data
{
	t_texture	*wall_texture;
	int			wall_height;
	int			wall_start;
	int			wall_end;
	double		wall_hit;
	int			texture_x;
	int			texture_y;
	double		texture_step;
	double		texture_pos;
};

struct s_render_floor_data
{
	double		fov_rad;
	double		ray_angle;
	t_vector	ray_dir;
	int			wall_height;
	int			wall_end;
	t_texture	*floor_tex;
};

struct s_ray
{
	t_vector	hit;
	double		distance;
	double		raw_distance;
	char		side;
};

void	render_game(t_main *g);
void	render_main_menu(t_main *g);
void	render_pause_menu(t_main *g);
void	render_select_map(t_main *g);
void	render_shop(t_main *g);
void	render_error_menu(t_main *g);
void	render_summary_menu(t_main *g);

void	put_pixel(int x, int y, int color, t_window *win);
void	render_background(t_main *g);
void	raycasting(t_main *g);
void	raycasting_right_rotation(t_main *g);
void	raycasting_left_rotation(t_main *g);
void	raycast_single(t_cast_data *d, char **matrix);
void	draw_wall_column(t_main *g, int x, t_ray *ray);
void	draw_floor_column(t_main *g, int x, t_ray *ray);
void	render_scene(t_main *g);
void	render_frames(t_main *g);

int		insert_doorwall_hit(t_cast_data *d, int player_location);
void	insert_vertical_hit(t_cast_data *d);
void	insert_horizontal_hit(t_cast_data *d);
int		find_intersection(t_cast_data *d, t_segment inner_wall);

void	render_map_time(t_main *g);
void	render_spellbook(t_main *g);
void	render_fps(long long curr_time, t_main *g);

void	update_object_segment(t_segment *obj_seg, t_vector obj_pos,
			t_player *player, double width);
int		is_segment_in_fov(t_player *p, t_segment *segment);
void	queue_add_orb(t_obj_node *node, t_main *g);
void	queue_add_fireball(t_obj_node *node, t_main *g);
void	queue_add_enemy(t_obj_node *node, t_main *g);
void	queue_add_particle(t_obj_node *node, t_main *g);
void	queue_add_door(t_obj_node *node, t_main *g);
void	create_render_queue(t_main *g);

void	render_objects(t_main *g);
void	render_door(t_main *g, t_door *door);
void	render_particle(t_main *g, t_fire_particle *particle);
void	render_fireball(t_main *g, t_fireball *f);
void	render_enemy(t_main *g, t_enemy *e);
void	render_orb(t_main *g, t_orb *orb);

t_ray	*get_ray_from_list(t_ray_list *list, int x);
double	get_hit_position(t_ray *ray, t_segment *seg);
int		get_image_column(double hit_position, t_im *image);
void	init_object_cast_data(t_cast_data *d, t_main *g, t_ray *ray);

#endif