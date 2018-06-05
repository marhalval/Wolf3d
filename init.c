/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvashchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 14:45:13 by hvashchu          #+#    #+#             */
/*   Updated: 2017/10/11 14:45:16 by hvashchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	load_texture(t_wolf *new)
{
	char		*array[10];
	void		*img;
	int			tmp;
	int			i;

	new->texture = (int **)malloc(sizeof(int *) * 10);
	array[0] = "pics/color.xpm";
	array[1] = "pics/mossy.xpm";
	array[2] = "pics/red.xpm";
	array[3] = "pics/purple.xpm";
	array[4] = "pics/door.xpm";
	array[5] = "pics/color.xpm";
	array[6] = "pics/barrel.xpm";
	array[7] = "pics/pillar.xpm";
	array[8] = "pics/stone.xpm";
	array[9] = "pics/wood.xpm";
	i = 0;
	while (i < 10)
	{
		img = mlx_xpm_file_to_image(new->mlx, array[i], &new->t_w, &new->t_h);
		if (img == NULL)
			exit(write(2, "error: can not load textures\n", 29));
		new->texture[i] = (int *)mlx_get_data_addr(img, &tmp, &tmp, &tmp);
		i++;
	}
}

t_me	*place_me(t_map *map)
{
	t_me	*me;
	t_i		i;

	me = ft_memalloc(sizeof(t_me));
	me->dir.x = 1;
	me->dir.y = 0;
	me->pln.x = 0;
	me->pln.y = 0.5;
	i.y = 0;
	while (i.y < map->height)
	{
		i.x = 0;
		while (i.x < map->width)
		{
			if (map->map[i.y][i.x] == 0)
			{
				me->pos.x = i.x + 0.4;
				me->pos.y = i.y + 0.4;
				return (me);
			}
			i.x++;
		}
		i.y++;
	}
	return (me);
}
