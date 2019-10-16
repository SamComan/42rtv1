/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:57:36 by krutten           #+#    #+#             */
/*   Updated: 2019/09/24 16:54:33 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rtv1.h"

int		cylinder_intersect(t_ray *ray, void *hit_object)
{
	double	a;
	double	b;
	double	c;
	t_vec3	oc;
	double	d;
	double	t1;
	double	t2;
    t_cyl	*specs;
	t_vec3	p1;
	t_vec3	p2;
	t_vec3	h1;
	t_vec3	h2;
	double	height1;
	double	height2;
//	double	m;
//	t_vec3	height;
	t_vec3	tmp;
	t_vec3	tmp2;
//	t_vec3	tmp3;
static int	first_entry;


	specs = (t_cyl *)hit_object;
	if (!first_entry)
		printf("t_cyl: center : %f, %f, %f \taxis: %f, %f, %f \n", specs->center.x, specs->center.y, specs->center.z, specs->axis.x, specs->axis.y, specs->axis.z );
	oc = vec3_combine_vec(&ray->origin, &specs->center, '-');
	if (!first_entry)
		printf("oc = %f, %f, %f\n", oc.x, oc.y, oc.z);
	a = 1 - (vec3_dot_product(ray->direct, specs->axis) * vec3_dot_product(ray->direct, specs->axis)); // D|D - (D|V)^2
	//a = (ray.direct - vec3_dot_product(ray->direct, specs->axis)
	b = 2 * (vec3_dot_product(ray->direct, oc) - (vec3_dot_product(ray->direct, specs->axis) * vec3_dot_product(oc, specs->axis)));  // 2* (D|X - (D|V)*(X|V))
	c = vec3_dot_product(oc, oc) - (vec3_dot_product(oc, specs->axis) * vec3_dot_product(oc, specs->axis)) - (specs->radius * specs->radius); //X|X - (X|V)^2 - r*r
	d = b * b - 4 * a * c;
	if (!first_entry)
	{
		printf("a = %f, b = %f, c = %f, d  = %f\n", a, b, c, d);
		printf("D|X = %f, X|X = %f, X|V = %f, d  = %f\n", vec3_dot_product(ray->direct, oc), vec3_dot_product(oc, oc), vec3_dot_product(oc, specs->axis), d);
	}
	first_entry = 1;
	if (d < 0)
	{
	//	printf("ray missed\n");
		return (0);
	}
	t1 = (- b + sqrt(d)) / (2 * a);
	t2 = (- b - sqrt(d)) / (2 * a);
	if (ray->origin.z != 7.0)
	//	printf("t1 %f t2 %f\n", t1, t2);
	if (t1 < NEAR && t2 < NEAR)
		return (0);
	p1 = vec3_scalar_product(ray->direct, t1, '*');
	p1 = vec3_combine_vec(&ray->origin, &p1, '+');
	h1 = vec3_combine_vec(&p1, &specs->center, '-');
	if ((height1 = vec3_dot_product(h1, specs->axis)) > specs->max || height1 < 0)
	{
		t1 = FAR;
//		if (p1.y < 4.05 && p1.y > 0)
//			printf("point out of cyl bounds at %f,%f,%f\n", p1.x, p1.y, p1.z);
	}
	p2 = vec3_scalar_product(ray->direct, t2, '*');
	p2 = vec3_combine_vec(&ray->origin, &p2, '+');
	h2 = vec3_combine_vec(&p2, &specs->center, '-');
	if ((height2 = vec3_dot_product(h2, specs->axis)) > specs->max || height2 < 0)
	{
//		if (p2.y < 4.05 && p2.y > 0)
//		printf("point out of cyl bounds at %f,%f,%f\n", p2.x, p2.y, p2.z);
		t2 = FAR;
	}
	if (t2 < t1 && t2 > NEAR)
	{
		t1 = t2;
		p1 = p2;
		height1 = height2;
	/*	m = vec3_dot_product(ray->direct, specs->axis) * ray->t + vec3_dot_product(oc, specs->axis);
		p1 = vec3_combine_vec(&p1, &specs->center, '+');
		ray->hitnormal = vec3_combine_vec(&p1, &specs->center, '-'); // N = nrm( P-C-V*m )
		height = vec3_scalar_product(specs->axis, m, '*');
		ray->hitnormal = vec3_combine_vec(&ray->hitnormal, &height, '-'); // N = nrm( P-C-V*m )
		ray->hitnormal = normalise(ray->hitnormal);*/
	}
	if (t1 < ray->t && ray->t > NEAR)
	{
		ray->near_col = specs->color;
		ray->t = t1;
	//	printf("t1 %f\n",ray->t);
		tmp = vec3_scalar_product(specs->axis, height1, '*');
		tmp2 = vec3_combine_vec(&specs->center, &tmp, '+');
	//	printf("closest on axis %f %f %f \n",tmp2.x, tmp2.y,tmp2.z);
		ray->hitnormal = vec3_combine_vec(&p1, &tmp2, '-');
		ray->hitnormal = normalise(ray->hitnormal);
	//	printf("normal %f %f %f \n",ray->hitnormal.x, ray->hitnormal.y,ray->hitnormal.z);
	/*	m = vec3_dot_product(ray->direct, specs->axis) * ray->t + vec3_dot_product(oc, specs->axis);
		p2 = vec3_combine_vec(&p2, &specs->center, '+');
		ray->hitnormal = vec3_combine_vec(&p2, &specs->center, '-'); // N = nrm( P-C-V*m )
		height = vec3_scalar_product(specs->axis, m, '*');
		ray->hitnormal = vec3_combine_vec(&ray->hitnormal, &height, '-'); // N = nrm( P-C-V*m )
		ray->hitnormal = normalise(ray->hitnormal);*/
	}
	//printf("intersections at %f, %f", t1, t2);
	cap_intersect_bot(ray, specs);
	cap_intersect_top(ray, specs);
	return (1);
}