/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krutten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 14:19:15 by krutten           #+#    #+#             */
/*   Updated: 2019/09/16 14:19:17 by krutten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rtv1.h"

t_vec3	normalise(float x, float y, float z) // this function just normalises vector to length 1 for later
{
	float	length;
	t_vec3	norm_vec;

	length = sqrt((x * x) + (y * y) + (z * z));
	norm_vec.x = x / length;
	norm_vec.y = y / length;
	norm_vec.z = z / length;
//	printf("pre-norm ray =%f,%f,%f\n", x, y, z);
//	printf("norm ray =%f,%f,%f\n", norm_vec.x, norm_vec.y, norm_vec.z);
	return (norm_vec);
}

t_vec3	pixel_to_world(float x, float y, t_rt *specs) // convert pixel coordinates to world coordinates so we can cast real world rays through screen pixels
{
	t_vec3	ray;

	ray.x = ((2.0 * x) - 1.0) * tan(specs->alpha / 2.0) * specs->aspect;
	ray.y = (1.0 - (2.0 * y)) * tan(specs->alpha / 2.0);
	ray.z = -1.0;
//	printf("coord %f, %f became %f, %f\n", x, y, ray.x, ray.y);
	return (ray);
}

int		spawn_ray(float x, float y, t_rt *specs)
{
	t_ray	ray;
	t_plane	plane;
	t_sphere	sphere;

	sphere.center.x = 0;
	sphere.center.y = 1;
	sphere.center.z = -10;
	sphere.radius = 2;
	plane.normal.x = 0;
	plane.normal.y = 1;
	plane.normal.z = 0;
	plane.point.x = 0;
	plane.point.y = -1;
	plane.point.z = 0;
	ray.origin = specs->camera;
	ray.direct = pixel_to_world(x, y, specs);
	ray.direct = normalise(ray.direct.x, ray.direct.y, ray.direct.z);
	ray.t = FAR;
	sphere_intersect(&ray, &sphere);
	plane_intersect(&ray, &plane);
	if (ray.t < FAR)
		return (1);
	return (0);
}

int		pixel_loop(char *img_str, void *mlx, void *win, void *img, t_rt *specs)
{
	int		x;
	int		y;
	
	y = -1;
	while (++y < 800)
	{
		x = -1;
		while (++x < 800)
		{
			if (spawn_ray(((float)x / 800),(float)y / 800, specs) == 1) // for each pixel construct ray
				img_str[(y * 800 + x) * 4] = 'a'; // for now 
			else
				img_str[(y * 800 + x) * 4] = '0';
		}
	}
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	return (0);
}

int				file_to_array(int fd, t_rt *specs)
{
	char		*line;
	int			i;
	int			j;

	i = -1;
	if (!(specs->input = (char **)malloc(sizeof(char *) * 500))) //for memory efficiency we could count the lines before allocating but fuck it
		return (0);
	while (get_next_line(fd, &line))
	{
		if(!(specs->input[++i] = (char *)malloc(sizeof(char) * ft_strlen(line) + 1)))
			return (0);
		j = -1;
		while (++j < ft_strlen(line))
			specs->input[i][j] = line[j];
		specs->input[i][ft_strlen(line)] = '\0';
		printf("wrote line into rt->input[%d]: %s\n", i, specs->input[i]);
		ft_strdel(&line);
	}
	specs->input[i + 1] = NULL;
	return (1);
}

t_rt			*init_rt_struct(int fd)
{
	t_rt		*new;

	if (!(new = (t_rt *)malloc(sizeof(t_rt))))
		return NULL;
	if (!(new->mlx = mlx_init()))
		return NULL;
	new->win = mlx_new_window(new->mlx, 800, 800, "RTV1");
	new->img = mlx_new_image(new->mlx, 800, 800);
	new->img_str = mlx_get_data_addr(new->img, &new->bpp, &new->size_line, &new->endian);
	new->camera.x = 0;
	new->camera.y = 0;
	new->camera.z = 0;
	new->view_dir.x = 0;
	new->view_dir.y = 0;
	new->view_dir.z = -1;
	new->alpha = (90.0/180.0) * M_PI; // radians transformation, replace 90 with any angle
	new->aspect = 1;
	if (!(file_to_array(fd, new))) //step 1 of parsing, make string array from input file
		return NULL;//exit protocol, t_rt needs to be freed as well as whole t_rt->input
	return (new);
}

int				main(int ac, char **av)
{
	t_rt		*specs;
	int			fd;
	if (ac != 2)
	{
		ft_putstr("Usage: ./rtv1 scenefile\n");
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	if (!(specs = init_rt_struct(fd)))
	{
		ft_putstr_fd("Failed to read input file\n", 2);
		return (0);
	}
	pixel_loop(specs->img_str, specs->mlx, specs->win, specs->img, specs);
	mlx_loop(specs->mlx);
	return (0);
}
