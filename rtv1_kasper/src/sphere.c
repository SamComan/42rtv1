/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:10:20 by krutten           #+#    #+#             */
/*   Updated: 2019/10/03 18:11:49 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	sphere_inter2(t_ray *ray, t_var *v)
{
	if (v->t2 < v->t1 && v->t2 > 0)
		v->t1 = v->t2;
	if (v->t1 < ray->t)
	{
		ray->near_col = v->s->color;
		ray->t = v->t1;
		intersection_vec3(ray);
		ray->hitnormal = normalise(vec3_combine_vec(&ray->hitpoint,
		&v->s->center, '-'));
	}
}

int		sphere_intersect(t_ray *ray, void *ptr)
{
	t_var v;

	v.s = (t_sphere *)ptr;
	v.oc = vec3_combine_vec(&ray->origin, &v.s->center, '-');
	v.ext = vec3_combine_vec(&ray->origin, &ray->direct, '+');
	v.ext = vec3_combine_vec(&v.ext, &v.s->center, '-');
	if (vec3_dot_product(v.ext, v.ext) > vec3_dot_product(v.oc, v.oc))
		return (0);
	v.b = 2 * vec3_dot_product(ray->direct, v.oc);
	v.c = vec3_dot_product(v.oc, v.oc) - (v.s->radius * v.s->radius);
	v.d = v.b * v.b - 4 * v.c;
	if (v.d < 0)
		return (0);
	v.t1 = (-v.b + sqrt(v.d)) / 2;
	v.t2 = (-v.b - sqrt(v.d)) / 2;
	sphere_inter2(ray, &v);
	return (1);
}
