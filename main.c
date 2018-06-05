/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvashchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 18:55:52 by hvashchu          #+#    #+#             */
/*   Updated: 2017/10/09 18:55:55 by hvashchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	exit_mouse(void)
{
	exit(0);
}

int			main(int argc, char **argv)
{
	t_wolf	*new;
	int		fd;

	if (argc != 2)
	{
		ft_putendl("Usage: ./wolf3d [map.txt]");
		exit(0);
	}
	fd = open(argv[1], O_RDONLY);
	new = ft_memalloc(sizeof(t_wolf));
	if (fd < 0 || (new->map = read_map(fd)) == NULL)
		exit(write(2, "error: invalid file\n", 20));
	new->mlx = mlx_init();
	new->win = mlx_new_window(new->mlx, WIDTH, HEIGHT, "wolf3d");
	load_texture(new);
	new->me = place_me(new->map);
	raycast(new);
	mlx_hook(new->win, 17, 1L << 17, exit_mouse, new);
	mlx_hook(new->win, 2, 5, key_hook, new);
	mlx_loop(new->mlx);
	return (0);
}
