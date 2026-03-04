/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:32:21 by yusudemi          #+#    #+#             */
/*   Updated: 2026/03/05 00:31:33 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "texture.h"
# include "../utils/utils.h"
# include "../player/player.h"

# define MAP_FOLDER		"_maps/"
# define CAMPAIGN_MAP "_maps/campaign1.cub"
# define MAP_FORMAT		".cub"
# define MAP_MAX_LEN	16

typedef struct s_map		t_map;
typedef struct s_main		t_main;
typedef struct s_map_file	t_map_file;
enum e_identifiers
{
	NO = 0,
	SO,
	WE,
	EA,
	FL,
	C,
	NEXT,
	MAP
};

struct s_map_file
{
	char	*file;
	char	*file_shown;
};

struct s_map
{
	t_map_file	*files;
	char		*next_map;
	t_texture	texture_no;
	t_texture	texture_so;
	t_texture	texture_we;
	t_texture	texture_ea;
	t_texture	texture_f;
	int			color_c;
	char		**matrix;
	t_player	player;
	long long	map_timer;
	void		*door_walls;
};

void	cub_map(t_map *map);
char	*reader(int fd);
char	*read_file(char	*map_file);

int		map_parse(char *raw_map, t_main *g);
int		load_map(char *map_location, t_main *game);
char	*read_file(char *map_file);
int		load_texture(char *raw_map, t_texture *target, t_main *game);
int		load_color(char *raw_map, int *target_color);
void	load_next_map_info(char *raw_map, t_main *game);
int		load_matrix(char *raw_map, t_main *game);
int		create_matrix(char *raw_map, t_main *game);
void	load_doors(char *raw_map, t_main *game);

#endif
