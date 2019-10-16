/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krutten <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:58:30 by krutten           #+#    #+#             */
/*   Updated: 2019/09/30 19:14:23 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		parse_scene(int *i, t_rt *specs)
{
	int		j;

	starter(i, &j, specs);
	parse_vec(&specs->camera, i, &j, specs);
	parse_vec_spec(&specs->view_dir, i, &j, specs);
}

void		parse_lights(int *i, t_rt *specs)
{
	int			j;
	int			len;
	char		*str;

	j = 0;
	printf("light parse\n");
	while (specs->input[*i][j] != '(')
		j++;
	len = j + 2;
	j++;
	while (specs->input[*i][len] != ')')
		len++;
	len = len - j;
	if (!(str = ft_strsub(specs->input[*i], j, len)))
		return ;
	if (!ft_strcmp(str, "spherical"))
	{
		printf("read sph light parse\n");
		parse_lights_s(i, specs);
	}
	if (!ft_strcmp(str, "distant"))
	{
		printf("read dist light parse\n");
		parse_lights_d(i, specs);
	}
	free(str);
}

void		parse_lights_s(int *i, t_rt *specs)
{
	int			j;
	t_light_s		*l;
	t_obj		*new;

	new = NULL;
	starter(i, &j, specs);
	if (!(l = (t_light_s *)malloc(sizeof(*l))))
		free_obj_list(&specs->light_list, "Can't create a light source!");
	parse_vec(&l->center, i, &j, specs);
	l->radius = ft_atof(move(i, &j, specs));
	l->color = ft_atoi_base(move(i, &j, specs), 16);
	l->intensity = ft_atof(move(i, &j, specs));
	if (!(new = new_object(l, 4)))
		free_obj_list(&specs->light_list, "Can't add a light source!");
	add_object(&specs->light_list, new);
}

void		parse_lights_d(int *i, t_rt *specs)
{
	int			j;
	t_light_d		*l;
	t_obj		*new;

	new = NULL;
	starter(i, &j, specs);
	if (!(l = (t_light_d *)malloc(sizeof(*l))))
		free_obj_list(&specs->light_list, "Can't create a light source!");
	parse_vec(&l->direct, i, &j, specs);
	l->direct = normalise(l->direct);
	l->radius = ft_atof(move(i, &j, specs));
	l->color = ft_atoi_base(move(i, &j, specs), 16);
	l->intensity = ft_atof(move(i, &j, specs));
	if (!(new = new_object(l, 5)))
		free_obj_list(&specs->light_list, "Can't add a light source!");
	add_object(&specs->light_list, new);
}

void		parse(t_rt *specs)
{
	int		i;
	t_obj	*objects;
	t_obj	*lights;

	i = -1;
	while (specs->input[++i])
	{
		if (!ft_strcmp(specs->input[i], "scene"))
			parse_scene(&i, specs);
		parse_lights(&i, specs);
		parse_objects(&i, specs);
	}
		printf(" \n CAMERA \n camera position x = %f, y = %f, z = %f \n camera direction x = %f, y = %f, z = %f\n",
	specs->camera.x, specs->camera.y,  specs->camera.z, specs->view_dir.x, specs->view_dir.y, specs->view_dir.z);

	// Running through the list of objects

	objects = specs->obj_list;
	lights = specs->light_list;
	while (objects)
	{
		if (objects->id == 0) // plane
		{
			printf(" \n PLANE \n intersection point x = %f y = %f z = %f, normal point x = %f y = %f z = %f color = %d\n",
			((t_plane *)objects->obj)->point.x, ((t_plane *)objects->obj)->point.y, ((t_plane *)objects->obj)->point.z,
			((t_plane *)objects->obj)->normal.x, ((t_plane *)objects->obj)->normal.y, ((t_plane *)objects->obj)->normal.z
			, ((t_plane *)objects->obj)->color);
		}
		else if (objects->id == 1) // sphere
		{
			printf(" \n SPHERE \n center x = %f y = %f z = %f, radius = %f, color = %d\n",
			((t_sphere *)objects->obj)->center.x, ((t_sphere *)objects->obj)->center.y, ((t_sphere *)objects->obj)->center.z,
			((t_sphere *)objects->obj)->radius, ((t_sphere *)objects->obj)->color);
		}
		else if (objects->id == 2) // cylinder
		{
			printf(" \n CYLINDER \n center x = %f y = %f z = %f, radius = %f, max = %f, axis x = %f y = %f z = %f color = %d\n",
			((t_cyl *)objects->obj)->center.x, ((t_cyl *)objects->obj)->center.y, ((t_cyl *)objects->obj)->center.z,
			((t_cyl *)objects->obj)->radius, ((t_cyl *)objects->obj)->max, ((t_cyl *)objects->obj)->axis.x, ((t_cyl *)objects->obj)->axis.y,
			((t_cyl *)objects->obj)->axis.z, ((t_cyl *)objects->obj)->color);
		}
		else if (objects->id == 3) // clone
		{
			printf(" \n CONE \n center x = %f y = %f z = %f, height = %f, max = %f, axis x = %f y = %f z = %f, min = %f, angle = %f\n",
			((t_cone *)objects->obj)->center.x, ((t_cone *)objects->obj)->center.y, ((t_cone *)objects->obj)->center.z,
			((t_cone *)objects->obj)->height, ((t_cone *)objects->obj)->max, ((t_cone *)objects->obj)->axis.x, ((t_cone *)objects->obj)->axis.y,
			((t_cone *)objects->obj)->axis.z, ((t_cone *)objects->obj)->min, ((t_cone *)objects->obj)->angle);   
		}
		objects = objects->next;
	}
	i = 0;
	while (lights && ++i)
	{
		if (lights->id == 4)
		{
			printf(" \n LIGHT %d \n center x = %f y = %f z = %f, radius = %f, color = %d, intensity = %f\n", i,
			((t_light_s *)lights->obj)->center.x, ((t_light_s *)lights->obj)->center.y, ((t_light_s *)lights->obj)->center.z,
			((t_light_s *)lights->obj)->radius, ((t_light_s *)lights->obj)->color, ((t_light_s *)lights->obj)->intensity);
		}
		else if (lights->id == 5)
		{
			printf(" \n LIGHT %d \n direct x = %f y = %f z = %f, radius = %f, color = %d, intensity = %f\n", i,
			((t_light_d *)lights->obj)->direct.x, ((t_light_d *)lights->obj)->direct.y, ((t_light_d *)lights->obj)->direct.z,
			((t_light_d *)lights->obj)->radius, ((t_light_d *)lights->obj)->color, ((t_light_d *)lights->obj)->intensity);
		}
		lights = lights->next;
	}
}
