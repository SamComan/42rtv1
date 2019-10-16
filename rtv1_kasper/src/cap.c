/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:29:57 by krutten           #+#    #+#             */
/*   Updated: 2019/09/30 21:57:49 by krutten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rtv1.h"

int		cap_intersect_bot(t_ray *ray, t_cyl *specs)
{
	t_vec3	oc;
	double	t;
	t_plane	p;
	double	dist;

	p.point = specs->center;
	p.normal = specs->axis;
	p.color = specs->color;
//	printf("entered from topcap cyl axis %f %f %f point %f %f %f\n", p.normal.x, p.normal.y, p.normal.z, p.point.x, p.point.y, p.point.z);
	oc = vec3_combine_vec(&ray->origin, &p.point, '-');
	if (vec3_dot_product(ray->direct, p.normal) == 0)
		return (0);
	t = (vec3_dot_product(oc, p.normal) * (-1))
		/ vec3_dot_product(ray->direct, p.normal);
	oc.x = ray->origin.x + t * ray->direct.x;
	oc.y = ray->origin.y + t * ray->direct.y;
	oc.z = ray->origin.z + t * ray->direct.z;
	dist = sqrt(pow(oc.x - p.point.x, 2) + pow(oc.y - p.point.y, 2) + pow(oc.z - p.point.z, 2));
//	printf("found collision t %f ray-> %f\n", t, ray->t);
	if (t < ray->t && t > NEAR && dist < specs->radius)
	{
//		printf("entered from topcap cyl axis %f %f %f point %f %f %f\n", p.normal.x, p.normal.y, p.normal.z, p.point.x, p.point.y, p.point.z);
		ray->t = t;
		ray->near_col = p.color;
		ray->hitnormal = p.normal;
		normal_towards_cam(ray);
		return (1);
	}
	return (0);
}

int		cap_intersect_top(t_ray *ray, t_cyl *specs)
{
	t_vec3	oc;
	double	t;
	t_plane	p;
	double	dist;

	p.point = vec3_scalar_product(specs->axis, specs->max, '*');
	p.point = vec3_combine_vec(&specs->center, &p.point, '+');
	p.normal = specs->axis;
	p.color = specs->color;
//	printf("entered from topcap cyl axis %f %f %f point %f %f %f\n", p.normal.x, p.normal.y, p.normal.z, p.point.x, p.point.y, p.point.z);
	oc = vec3_combine_vec(&ray->origin, &p.point, '-');
	if (vec3_dot_product(ray->direct, p.normal) == 0)
		return (0);
	t = (vec3_dot_product(oc, p.normal) * (-1))
		/ vec3_dot_product(ray->direct, p.normal);
	oc.x = ray->origin.x + t * ray->direct.x;
	oc.y = ray->origin.y + t * ray->direct.y;
	oc.z = ray->origin.z + t * ray->direct.z;
	dist = sqrt(pow(oc.x - p.point.x, 2) + pow(oc.y - p.point.y, 2) + pow(oc.z - p.point.z, 2));
//	printf("found collision t %f ray-> %f\n", t, ray->t);
	if (t < ray->t && t > NEAR && dist < specs->radius)
	{
//		printf("entered from topcap cyl axis %f %f %f point %f %f %f\n", p.normal.x, p.normal.y, p.normal.z, p.point.x, p.point.y, p.point.z);
		ray->t = t;
		ray->near_col = p.color;
		ray->hitnormal = p.normal;
		normal_towards_cam(ray);
		return (1);
	}
	return (0);
}

int		cone_cap_intersect_bot(t_ray *ray, t_cone *specs)
{
	t_vec3	oc;
	double	t;
	t_plane	p;
	double	dist;
	double	rad;

	p.point = vec3_scalar_product(specs->axis, specs->min, '*');
	p.point = vec3_combine_vec(&specs->center, &p.point, '+');
	p.normal = specs->axis;
	p.color = specs->color;
//	printf("entered from topcap cyl axis %f %f %f point %f %f %f\n", p.normal.x, p.normal.y, p.normal.z, p.point.x, p.point.y, p.point.z);
	oc = vec3_combine_vec(&ray->origin, &p.point, '-');
	if (vec3_dot_product(ray->direct, p.normal) == 0)
		return (0);
	t = (vec3_dot_product(oc, p.normal) * (-1))
		/ vec3_dot_product(ray->direct, p.normal);
	oc.x = ray->origin.x + t * ray->direct.x;
	oc.y = ray->origin.y + t * ray->direct.y;
	oc.z = ray->origin.z + t * ray->direct.z;
	dist = sqrt(pow(oc.x - p.point.x, 2) + pow(oc.y - p.point.y, 2) + pow(oc.z - p.point.z, 2));
//	printf("found collision t %f ray-> %f\n", t, ray->t);
	rad = tan(specs->angle) * ABS(specs->min);
	if (t < ray->t && t > NEAR && dist < rad)
	{
//		printf("entered from topcap cyl axis %f %f %f point %f %f %f\n", p.normal.x, p.normal.y, p.normal.z, p.point.x, p.point.y, p.point.z);
		ray->t = t;
		ray->near_col = p.color;
		ray->hitnormal = p.normal;
		normal_towards_cam(ray);
		return (1);
	}
	return (0);
}

int		cone_cap_intersect_top(t_ray *ray, t_cone *specs)
{
	t_vec3	oc;
	double	t;
	t_plane	p;
	double	dist;
	double	rad;

	p.point = vec3_scalar_product(specs->axis, specs->max, '*');
	p.point = vec3_combine_vec(&specs->center, &p.point, '+');
	p.normal = specs->axis;
	p.color = specs->color;
//	printf("entered from topcap cyl axis %f %f %f point %f %f %f\n", p.normal.x, p.normal.y, p.normal.z, p.point.x, p.point.y, p.point.z);
	oc = vec3_combine_vec(&ray->origin, &p.point, '-');
	if (vec3_dot_product(ray->direct, p.normal) == 0)
		return (0);
	t = (vec3_dot_product(oc, p.normal) * (-1))
		/ vec3_dot_product(ray->direct, p.normal);
	oc.x = ray->origin.x + t * ray->direct.x;
	oc.y = ray->origin.y + t * ray->direct.y;
	oc.z = ray->origin.z + t * ray->direct.z;
	dist = sqrt(pow(oc.x - p.point.x, 2) + pow(oc.y - p.point.y, 2) + pow(oc.z - p.point.z, 2));
	rad = tan(specs->angle) * ABS(specs->max);
//	printf("found collision t %f ray-> %f\n", t, ray->t);
	if (t < ray->t && t > NEAR && dist < rad)
	{
//		printf("entered from topcap cyl axis %f %f %f point %f %f %f\n", p.normal.x, p.normal.y, p.normal.z, p.point.x, p.point.y, p.point.z);
		ray->t = t;
		ray->near_col = p.color;
		ray->hitnormal = p.normal;
		normal_towards_cam(ray);
		return (1);
	}
//	printf ("leaving topcap without colliding ??????, t %f , rayt %f, point %f %f %f, dist %f\n", t, ray->t, p.point.x, p.point.y, p.point.z, dist);
	return (0);
}