/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:32:21 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/20 00:04:51 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

#include "texture.h"
#include "../utils/utils.h"
#include "../player/player.h"

# define MAP_FOLDER		"testmaps/"
# define CAMPAIGN_MAP "testmaps/valid_wall.cub"
# define MAP_FORMAT		".cub"

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
	int		validated; // if map valid = 1 if not valid = -1 if not validated yet = 0
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
};

void	cub_map(t_map *map);

void	load_map(char *map_location, t_main *game);
char	*read_file(char *map_file);
void	load_texture(char *raw_map, t_texture *target, char *identifier, t_main *game);
void	load_color(char *raw_map, int *target_color, char *identifier);
void	load_next_map_info(char *raw_map, t_main *game);
void	validate_map(char *raw_map);
void	load_matrix(char *raw_map, t_main *game);
int		create_matrix(char *raw_map, t_main *game);
void	map_cleanup_exit(char *errmsg, t_main *game);
void	map_cleanup(t_main *game);
void	load_doors(char *raw_map);

#endif
