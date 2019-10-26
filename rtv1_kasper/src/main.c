/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 14:19:15 by krutten           #+#    #+#             */
/*   Updated: 2019/10/03 18:00:45 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			spawn_ray(float x, float y, t_rt *specs)
{
	t_var	v;
	t_ray	ray;
	t_obj	*o;

	o = specs->obj_list;
	ray.origin = specs->camera;
	ray.direct = pixel_to_world(x, y, specs);
	ray.direct = normalise(ray.direct);
	ray.t = FAR;
	ray.near_col = 0x88;
	loop_ray_over_objects(&ray, specs);
	if (ray.t < FAR)
	{
		lighting(&ray, specs);
		v.red = ((ray.near_col >> 16) & 0xff) * ray.illum;
		v.green = ((ray.near_col >> 8) & 0xff) * ray.illum;
		v.blue = (ray.near_col & 0xff) * ray.illum;
		ray.near_col = (v.red << 16) | (v.green << 8) | v.blue;
		return (ray.near_col);
	}
	return (-1);
}

int			pixel_loop(t_rt *specs)
{
	int		x;
	int		y;
	int		color;

	y = -1;
	while (++y < H_IMG)
	{
		x = -1;
		while (++x < W_IMG)
		{
			if ((color = spawn_ray(((float)x / W_IMG),
			(float)y / H_IMG, specs)) != -1)
			{
				specs->img_str[(y * W_IMG + x) * 4] = color & 0xff;
				specs->img_str[(y * W_IMG + x) * 4 + 1] = (color >> 8) & 0xff;
				specs->img_str[(y * W_IMG + x) * 4 + 2] = (color >> 16) & 0xff;
			}
			else
				specs->img_str[(y * W_IMG + x) * 4] = '0';
		}
	}
	return (0);
}

int			file_to_array(int fd, t_rt *specs) // free specs->input
{
	char		*line;
	int			i;
	int			j;

	i = -1;
	if (!(specs->input = (char **)malloc(sizeof(char *) * 500)))
		return (0);
	while (get_next_line(fd, &line))
	{
		if (!(specs->input[++i] = (char *)malloc(sizeof(char) *
		ft_strlen(line) + 1)))
			return (0);
		j = -1;
		while (++j < (int)ft_strlen(line))
			specs->input[i][j] = line[j];
			printf("i = %d, j = %d, input[%d][%d] = %c\n", i,j,i,j,specs->input[i][j]);
		specs->input[i][ft_strlen(line)] = '\0';
		ft_strdel(&line);
	}
	specs->input[i + 1] = NULL; 
	return (1);
}

int			init_rt_struct(int fd, t_rt *new)
{
	if (!(new->mlx = mlx_init()))
		return (0);
	new->fct_ptr[0] = plane_intersect;
	new->fct_ptr[1] = sphere_intersect;
	new->fct_ptr[2] = cylinder_intersect;
	new->fct_ptr[3] = cone_intersect;
	new->win = mlx_new_window(new->mlx, WIDTH, HEIGHT, "rtv1");
	new->alpha = (90.0 / 180.0) * M_PI;
	new->aspect = H_IMG / W_IMG;
	new->obj_list = NULL;
	new->light_list = NULL;
	new->first = 0;
	if (!(file_to_array(fd, new)))
		return (0);
	return (1);
}

void		draw_image(t_rt *specs)
{
	specs->img = mlx_new_image(specs->mlx, W_IMG, H_IMG);
	specs->img_str = mlx_get_data_addr(specs->img, &specs->bpp,
	&specs->size_line, &specs->endian);
	//printf("x = %f, y = %f, z = %f\n", specs->view_dir.x, specs->view_dir.y, specs->view_dir.z);
	pixel_loop(specs);
	mlx_put_image_to_window(specs->mlx, specs->win, specs->img, 0, 0);
	mlx_destroy_image(specs->mlx, specs->img);
}

int			main(int ac, char **av)
{
	t_rt		specs;
	int			fd;

	if (ac != 2)
	{
		ft_putstr("Usage: ./rtv1 scenefile\n");
		return (0);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		perror("");
		return (0);
	}
	if (!init_rt_struct(fd, &specs))
	{
		ft_putstr_fd("Failed to read input file\n", 2);
		return (0);
	}
	parse(&specs);
	specs.view_dir = normalise(specs.view_dir);
	draw_image(&specs);
	mlx_key_hook(specs.win, deal_key, &specs);
	//mlx_loop(specs.mlx);
	return (0);
}
