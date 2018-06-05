/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvashchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 17:29:35 by hvashchu          #+#    #+#             */
/*   Updated: 2017/10/10 17:29:39 by hvashchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		check_map(t_map *map)
{
	int		x;
	int		y;
	int		full;

	full = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == 0)
				full = 1;
			if (map->map[y][x] < 0 || map->map[y][x] > 8)
				exit(write(2, "error: invalid map\n", 19));
			if (map->map[y][x] == 0 && (x == 0
				|| x == map->width - 1 || y == 0 || y == map->height - 1))
				exit(write(2, "error: invalid map\n", 19));
			x++;
		}
		y++;
	}
	if (full == 0)
		exit(write(2, "error: invalid map\n", 19));
}

char			*check_item(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			exit(write(2, "error: invalid map\n", 19));
		i++;
	}
	return (str);
}

static t_list	*get_map_list(int fd)
{
	char	*line;
	t_list	*list;
	int		i;
	int		n;
	char	**array;

	list = NULL;
	line = NULL;
	n = -1;
	while ((i = get_next_line(fd, &line)) > 0)
	{
		array = ft_strsplit(line, ',');
		if (n == -1)
			n = ft_arrlen(array);
		if (ft_strlen(line) == 0 || ft_arrlen(array) == 0
			|| ft_arrlen(array) != n)
			exit(write(2, "error: invalid map\n", 19));
		ft_lstaddback(&list, ft_lstnew(line, ft_strlen(line) + 1));
		ft_strdel(&line);
		ft_arrdel(array);
	}
	if (i == -1)
		exit(write(2, "error: invalid file\n", 20));
	return (list);
}

static t_map	*make_map(int width, int height, t_list *map_list)
{
	t_map	*map;
	t_list	*list;
	char	**array;
	t_i		i;

	list = map_list;
	map = ft_memalloc(sizeof(t_map));
	map->map = (int **)malloc(sizeof(int *) * height);
	i.y = 0;
	while (i.y < height)
	{
		i.x = 0;
		array = ft_strsplit(list->content, ',');
		map->map[i.y] = (int *)malloc(sizeof(int) * width);
		while (i.x < width)
		{
			map->map[i.y][i.x] = ft_atoi(check_item(array[i.x]));
			i.x++;
		}
		ft_arrdel(array);
		list = list->next;
		i.y++;
	}
	ft_lstclean(map_list);
	return (map);
}

t_map			*read_map(int fd)
{
	t_map	*map;
	t_list	*list;
	int		width;
	int		height;
	char	**array;

	if ((list = get_map_list(fd)) == NULL)
		exit(write(2, "error: empty map\n", 17));
	array = ft_strsplit(list->content, ',');
	height = ft_lstlen(list);
	width = ft_arrlen(array);
	ft_arrdel(array);
	map = make_map(width, height, list);
	map->width = width;
	map->height = height;
	check_map(map);
	return (map);
}
