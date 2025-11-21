/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 07:07:17 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/21 04:50:05 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <stdlib.h>
#include <ctype.h>

static int	validate_format(char *color, int len, t_main *g)
{
	int	i;
	int	commas;
	int	comma_seen;

	i = -1;
	commas = 0;
	comma_seen = 1;
	while (++i < len)
	{
		if (color[i] == ',' && comma_seen == 0)
		{
			comma_seen = 1;
			commas++;
		}
		else if (color[i] >= '0' && color[i] <= '9')
		{
			comma_seen = 0;
			continue ;
		}
	}
	if (comma_seen == 1 || commas != 2)
		return (1);
	return (0);
}

static int	extract_rgb_component(char **str, t_main *g)
{
	int	value;

	value = 0;
	while (**str >= '0' && **str <= '9')
	{
		value = value * 10 + (**str - '0');
		if (value > 255)
			return (-1);
		(*str)++;
	}
	return (value);
}

static int	str_to_rgb(char	*color, t_main *g)
{
	int rgb[3];
	int	i;

	i = 0;
	while (i < 3)
	{
		rgb[i] = extract_rgb_component(&color, g);
		if (rgb[i] == -1)
			return (-1);
		if (i < 2)
		{
			if (*color == ',')
				color++;
			else
				return (-1);
		}
		i++;
	}
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}
static int	extract_color(char *color_start, t_main *g)
{
	char	*color_end;
	int		color_len;

	color_start++;
	while (*color_start && isspace(*color_start))
		color_start++;
	color_end = color_start;
	while (*color_end && !isspace(*color_end))
		color_end++;
	color_len = color_end - color_start;
	if (color_len < 5)
		return (-1);
	if (validate_format(color_start, color_len, g))
		return (-1);
	return (str_to_rgb(color_start, g));
}

int	load_color(char *raw_map, int *target_color, char *identifier, t_main *g)
{
	int	rgb;

	if (*target_color != -1)
		return (1);
	rgb = extract_color(raw_map, g);
	if (rgb == -1)
		return (1);
	*target_color = rgb;
	return (0);
}
