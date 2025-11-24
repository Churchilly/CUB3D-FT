/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 07:07:17 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/24 09:56:39 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main/main.h"
#include <stdlib.h>
#include <ctype.h>

static int	validate_format(char *color, int len)
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

static int	extract_rgb_component(char **str)
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

static int	str_to_rgb(char	*color)
{
	int rgb[3];
	int	i;

	i = 0;
	while (i < 3)
	{
		rgb[i] = extract_rgb_component(&color);
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
static int	extract_color(char *color_start)
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
	if (validate_format(color_start, color_len))
		return (-1);
	return (str_to_rgb(color_start));
}

int	load_color(char *raw_map, int *target_color)
{
	int	rgb;
	if (*target_color != -1)
		return (1);
	rgb = extract_color(raw_map);
	if (rgb == -1)
		return (1);
	*target_color = rgb;
	return (0);
}
