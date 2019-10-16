/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:38:35 by rkamegne          #+#    #+#             */
/*   Updated: 2019/09/30 16:55:55 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	parse_sphere(int *i, t_rt *specs)
{
	int			j;
	t_sphere	*s;
	t_obj		*new;

	new = NULL;
	starter(i, &j, specs);
	if (!(s = (t_sphere *)malloc(sizeof(*s))))
		free_obj_list(&specs->obj_list, "Can't create a sphere!");
	parse_vec(&s->center, i, &j, specs);
	s->color = ft_atoi_base(move(i, &j, specs), 16);
	s->radius = ft_atof(move(i, &j, specs));
	if (!(new = new_object(s, 1)))
		free_obj_list(&specs->obj_list, "Can't add a sphere!");
	add_object(&specs->obj_list, new);
}

void	parse_cylinder(int *i, t_rt *specs)
{
	int			j;
	t_cyl		*c;
	t_obj		*new;

	new = NULL;
	starter(i, &j, specs);
	if (!(c = (t_cyl *)malloc(sizeof(*c))))
		free_obj_list(&specs->obj_list, "Can't create a cylinder!");
	parse_vec(&c->center, i, &j, specs);
	parse_vec_spec(&c->axis, i, &j, specs);
	c->max = ft_atof(move(i, &j, specs));
	c->radius = ft_atof(move(i, &j, specs));
	c->color = ft_atoi_base(move(i, &j, specs), 16);
	c->computed = 0;
	if (!(new = new_object(c, 2)))
		free_obj_list(&specs->obj_list, "Can't add a cylinder!");
	add_object(&specs->obj_list, new);
}

void	parse_plane(int *i, t_rt *specs)
{
	int			j;
	t_plane		*p;
	t_obj		*new;

	new = NULL;
	starter(i, &j, specs);
	if (!(p = (t_plane *)malloc(sizeof(*p))))
		free_obj_list(&specs->obj_list, "Can't create a plane!");
	parse_vec(&p->point, i, &j, specs);
	parse_vec_spec(&p->normal, i, &j, specs);
	p->color = ft_atoi_base(move(i, &j, specs), 16);
	if (!(new = new_object(p, 0)))
		free_obj_list(&specs->obj_list, "Can't add a plane!");
	add_object(&specs->obj_list, new);
}

void	parse_cone(int *i, t_rt *specs)
{
	int			j;
	t_cone		*c;
	t_obj		*new;

	new = NULL;
	starter(i, &j, specs);
	if (!(c = (t_cone *)malloc(sizeof(*c))))
		free_obj_list(&specs->obj_list, "Can't create a cone!");
	parse_vec(&c->center, i, &j, specs);
	parse_vec_spec(&c->axis, i, &j, specs);
	c->height = ft_atof(move(i, &j, specs));
	c->max = ft_atof(move(i, &j, specs));
	c->min = ft_atof(move(i, &j, specs));
	c->angle = ft_atof(move(i, &j, specs));
	c->color = ft_atoi_base(move(i, &j, specs), 16);
	c->computed = 0;
	if (!(new = new_object(c, 3)))
		free_obj_list(&specs->obj_list, "Can't add a cone!");
	add_object(&specs->obj_list, new);
}

void	parse_objects(int *i, t_rt *specs)
{
	int			j;
	int			len;
	char		*str;

	j = 0;
	while (specs->input[*i][j] != '(')
		j++;
	len = j + 2;
	j++;
	while (specs->input[*i][len] != ')')
		len++;
	len = len - j;
	if (!(str = ft_strsub(specs->input[*i], j, len)))
		return ;
	if (!ft_strcmp(str, "sphere"))
		parse_sphere(i, specs);
	if (!ft_strcmp(str, "cylinder"))
		parse_cylinder(i, specs);
	if (!ft_strcmp(str, "cone"))
		parse_cone(i, specs);
	if (!ft_strcmp(str, "plane"))
		parse_plane(i, specs);
	free(str);
}
