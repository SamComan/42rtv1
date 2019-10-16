/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:29:57 by krutten           #+#    #+#             */
/*   Updated: 2019/09/30 13:19:29 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	normal_towards_cam(t_ray *ray)
{
	double	len1;
	double	len2;
	t_vec3	tmp;

	tmp = vec3_combine_vec(&ray->origin, &ray->hitpoint, '-');
	len1 = sqrt(vec3_dot_product(tmp, tmp));
	tmp = vec3_scalar_product(ray->hitnormal, 0.05, '*');//i feel like this could be significantly simpler with an elegant vector product
	tmp = vec3_combine_vec(&ray->hitpoint, &tmp, '+');
	tmp = vec3_combine_vec(&ray->origin, &tmp, '-');
	len2 = sqrt(vec3_dot_product(tmp, tmp));
	if (len2 > len1)
		ray->hitnormal = vec3_scalar_product(ray->hitnormal, -1.0, '*');
}

int		plane_intersect(t_ray *ray, void *hit_object)
{
	t_vec3	oc;
	double	t;
	t_plane	*p;

	p = (t_plane *)hit_object;
//	printf("entered from topcap cyl axis %f %f %f point %f %f %f\n", p->normal.x, p->normal.y, p->normal.z, p->point.x, p->point.y, p->point.z);
	oc = vec3_combine_vec(&ray->origin, &p->point, '-');
	if (vec3_dot_product(ray->direct, p->normal) == 0)
		return (0);
	t = (vec3_dot_product(oc, p->normal) * (-1))
		/ vec3_dot_product(ray->direct, p->normal);
//	printf("found collision t %f ray-> %f\n", t, ray->t);
	if (t < ray->t && t > NEAR)
	{
//		printf("entered from topcap cyl axis %f %f %f point %f %f %f\n", p->normal.x, p->normal.y, p->normal.z, p->point.x, p->point.y, p->point.z);
		ray->t = t;
		ray->near_col = p->color;
		ray->hitnormal = p->normal;
		normal_towards_cam(ray);
//		ray->plane = 1;
		return (1);
	}
	return (0);
}
