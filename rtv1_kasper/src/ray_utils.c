/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 19:00:21 by rkamegne          #+#    #+#             */
/*   Updated: 2019/10/03 17:58:26 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3		normalise(t_vec3 v1)
{
	float	length;
	t_vec3	norm_vec;

	length = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
	norm_vec.x = v1.x / length;
	norm_vec.y = v1.y / length;
	norm_vec.z = v1.z / length;
	return (norm_vec);
}

void		rot_from_base2(double a, t_vec3 *u, t_mat3 *o)
{
	o->m[0][0] = cos(a) + u->x * u->x * (1 - cos(a));
	o->m[0][1] = u->x * u->y * (1 - cos(a)) - u->z * sin(a);
	o->m[0][2] = u->x * u->z * (1 - cos(a)) + u->y * sin(a);
	o->m[1][0] = u->y * u->x * (1 - cos(a)) + u->z * sin(a);
	o->m[1][1] = cos(a) + u->y * u->y * (1 - cos(a));
	o->m[1][2] = u->y * u->z * (1 - cos(a)) - u->x * sin(a);
	o->m[2][0] = u->z * u->x * (1 - cos(a)) - u->y * sin(a);
	o->m[2][1] = u->z * u->y * (1 - cos(a)) + u->x * sin(a);
	o->m[2][2] = cos(a) + u->z * u->z * (1 - cos(a));
}

t_mat3		rot_from_base(t_vec3 view, t_vec3 base, int wrong)
{
	double	a;
	t_vec3	u;
	t_mat3	o;
	t_vec3	comp;

	a = acos(vec3_dot_product(view, base));
	if (wrong == 1)
		a = -a;
	u = vec3_cross_product(view, base);
	u = normalise(u);
	if (a == 0)
	{
		o = mat3_unit();
		return (o);
	}
	rot_from_base2(a, &u, &o);
	comp = vector_matrix_multiply(base, o);
	comp = normalise(comp);
	if (vec3_dot_product(comp, view) < 0.999)
		return (rot_from_base(view, base, 1));
	return (o);
}

t_vec3		pixel_to_world(float x, float y, t_rt *specs)
{
	t_vec3		ray;
	t_vec3		base;

	base = vec3_init(0, 0, -1);
	if (specs->first++ == 0)
		specs->view_rot = rot_from_base(specs->view_dir, base, 0);
	ray.x = ((2.0 * x) - 1.0) * tan(specs->alpha / 2) * specs->aspect;
	ray.y = (1.0 - (2.0 * y)) * tan(specs->alpha / 2);
	ray.z = -1.0;
	ray = normalise(ray);
	ray = vector_matrix_multiply(ray, specs->view_rot);
	return (ray);
}

void		loop_ray_over_objects(t_ray *ray, t_rt *specs)
{
	t_obj	*o;

	o = specs->obj_list;
	while (o)
	{
		specs->fct_ptr[o->id](ray, o->obj);
		o = o->next;
	}
}
