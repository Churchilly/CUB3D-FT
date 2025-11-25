/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:19:16 by root              #+#    #+#             */
/*   Updated: 2025/11/24 16:47:19 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3_images.h"
#include "../utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "../garbage_collector/garbage_collector.h"
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "../map/map.h"

static int init_cub3_image(t_cub3_image *img, char *first_line)
{
    char **attr;
    
    if (!first_line || !*first_line || strlen(first_line) < 9)
        return (0);
    
    attr = ft_split(first_line, ':', TEMPORARY);
    if (!attr[2] || !attr[2][0])
        return (0);
    
    img->width = atoi(attr[1]);
    img->height = atoi(attr[2]); 

    if (!(img->width) || !(img->height))
        return (0);
    return (1);
}

static int write_line_to_image(char *line, t_cub3_image *img, int stat)
{
    static int counter = 0;
    int line_counter;
    char **parsed_line;

    if (stat == RESET)
    {
        counter = 0;
        return (RESET);
    }
    parsed_line = ft_split(line, '.', TEMPORARY);
    line_counter = 0;
    while (parsed_line[line_counter])
    {
        img->image[counter] = (int)strtol(parsed_line[line_counter], NULL, 16);
        counter++;
        line_counter++;
    }
    return (1);
}

static int read_cub3_image_content(t_cub3_image *img, char **lines)
{
    int line_counter;
    int i;

    img->image = alloc(img->height * img->width * sizeof(int), STATIC);
    line_counter = img->height;
    i = 1;
    while (line_counter--)
    {
        if (!lines[i] || strlen(lines[i]) < 8)
            return (0);
        write_line_to_image(lines[i], img, CONTINUE);
        i++;
    }
    write_line_to_image(NULL, NULL, RESET);
    return (1);
}

char *file_content(char *path)
{
    char *content;
    FILE *fp;
    long size;
    
    content = NULL;
    fp = fopen(path, "r");
    if (fp)
    {
        fseek(fp, 0, SEEK_END);
        size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        if (size <= 0)
            return (NULL);
        content = alloc(size, TEMPORARY);
        fread(content, 1, size, fp);
        fclose(fp);
        return (content);
    }
    return (NULL);
}

t_cub3_image create_image(char *path)
{
    char *content;
    char **lines;
    t_cub3_image new_image;
    t_cub3_image empty;

    empty = (t_cub3_image){NULL, 0, 0};
    content = file_content(path);
    if (content == NULL && printf("fail path (null): %s\n", path))
        return (empty);
    lines = ft_split(content, '\n', TEMPORARY);
    if (!init_cub3_image(&new_image, lines[0]) && printf("fail path: %s\n", path))
        return (empty);
    if (!read_cub3_image_content(&new_image, lines) && printf("exit3\n"))
        return (empty);
    clear_section(TEMPORARY);
    return (new_image);
}
