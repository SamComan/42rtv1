/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:57:40 by krutten           #+#    #+#             */
/*   Updated: 2019/09/27 11:35:05 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/rtv1.h"

int		cone_intersectbad(t_ray *ray, void *hit_object)////check func name
{
	double	a;
	double	b;
	double	c;
	//t_vec3	oc;
	double	d;
	double	t1;
	double	t2;
    t_cone	*specs;
	t_ray	local;
	double	y1;
	double	y2;
	t_vec3	base;
	double	tmp;

	specs = (t_cone *)hit_object;
	if (!specs->computed++)
	{
		base = vec3_init(0, 1, 0);
		specs->rot = rot_from_base(specs->axis, base, 0); // compute rotation from base 010 vector to t_cyl->axis vector
		specs->scale = mat3_unit();
		print_mat3(specs->rot);
		specs->scale.m[0][0] = specs->angle / 90;
		specs->scale.m[2][2] = specs->angle / 90;
		specs->scale.m[1][1] = 1.0;
		specs->rot_inv = mat3_inv(specs->rot); // invert rotation and apply to rotation
		specs->scale_inv = mat3_inv(specs->scale);
		print_mat3(specs->scale);
		printf("min %f max %f\n", specs->min, specs->max);
	}
	local = *ray;
	local.direct = vector_matrix_multiply(local.direct, specs->rot_inv); // rotating direction
	local.direct = vector_matrix_multiply(local.direct, specs->scale_inv); // scaling direction
	local.origin.x = local.origin.x - specs->center.x;
	local.origin.y = local.origin.y - specs->center.y;
	local.origin.z = local.origin.z - specs->center.z;
	local.origin = vector_matrix_multiply(local.origin, specs->rot_inv); // rotating origin
	local.origin = vector_matrix_multiply(local.origin, specs->scale_inv); // scaling origin
	a = pow(local.direct.x, 2) + pow(local.direct.z, 2) - pow(local.direct.y, 2);
	b = 2 * local.origin.x * local.direct.x + 2 * local.origin.z * local.direct.z - 2 * local.origin.y * local.direct.y;
	c = pow(local.origin.x, 2) + pow(local.origin.z, 2) - pow(local.origin.y, 2);
	d = b * b - 4 * a * c;
//	printf("d = %f\n",d);
	if (d < 0)
		return (0);
	t1 = (- b + sqrt(d)) / (2 * a);
	t2 = (- b - sqrt(d)) / (2 * a);
	if ((t1 > t2 && t2 > NEAR) || t1 < NEAR)
	{
		tmp = t1;
		t1 = t2;
		t2 = tmp;
	}
	if (t1 < NEAR)
		return (0);
//	if (t1 < ray->t)
//	{
//		ray->near_col = specs->color;
//		ray->t = t1;
//	}
//t_vec3	p1;
//t_vec3	p2;
	y1 = local.origin.y + t1 * local.direct.y;
//	p1 = vec3_scalar_product(local.direct, t1, '*');
//	p1 = vec3_combine_vec(&p1, &local.origin, '+');
	y2 = local.origin.y + t2 * local.direct.y;
//	y1 = vec3_dot_product(specs->axis, p1);

//	p2 = vec3_scalar_product(local.direct, t2, '*');
//	p2 = vec3_combine_vec(&p2, &local.origin, '+');
//	y2 = vec3_dot_product(specs->axis, p2);
//	if (y1 < 0)
//		y1 = -y1;
//	if (y2 < 0)
//		y2 = -y2;
	//printf("y1 %f y2 %f\n", y1, y2);
	t_vec3	ax1, ax2, ax3;
	double	h, h3;
	if ((y1 >= specs->min && y1 <= specs->max) || (y2 >= specs->min && y2 <= specs->max))
	{
		if (t1 < ray->t)
		{
			ray->near_col = specs->color;
			ray->t = t1;
			if (ray->origin.z == 10.0)
				intersection_vec3(ray);
			else
			{
				return (0);
			}
			
			ax1 = vec3_combine_vec(&ray->hitpoint, &specs->center, '-');
			h = vec3_dot_product(ax1, specs->axis);
			ax2 = vec3_scalar_product(specs->axis, h, '*');
			ax2 = vec3_combine_vec(&specs->center, &ax2, '+');
			ax2 = vec3_combine_vec(&ray->hitpoint, &ax2, '-'); // now contains the vec perpendicular to axis to intersect pt
			ax2 = normalise(ax2);
			ax3 = ax2;
			h3 = h;
			//ray->origin.z = 100;
		//	printf("h = %f, ax1 %f %f %f, hitpoint %f %f %f\n", h, ax1.x, ax1.y, ax1.z, ray->hitpoint.x, ray->hitpoint.y, ray->hitpoint.z);
			while (h3 < 100)
			{
				h3 += 0.05;
				ax3 = vec3_scalar_product(specs->axis, h3, '*');
				ax3 = vec3_combine_vec(&specs->center, &ax3, '+');
				ax3 = vec3_combine_vec(&ray->hitpoint, &ax3, '-');
				ax3 = normalise(ax3);
	//			printf("iterating to find normal %f, cos of angle %f h = %f\n",vec3_dot_product(ax2, ax3), cos(specs->angle/2 * (M_PI/180)),h);
				if (ABS(vec3_dot_product(ax2, ax3) - cos(specs->angle/2 * (M_PI/180))) < 0.005)
				{
					printf("dot product %f, cos of angle %f h = %f\n",vec3_dot_product(ax2, ax3), cos(specs->angle/2 * (M_PI/180)),h3);
					break;
				}
			}
			if (h3 == 100)
			{
				while (h3 > -100)
				{
					h3 -= 0.05;
					ax3 = vec3_scalar_product(specs->axis, h3, '*');
					ax3 = vec3_combine_vec(&specs->center, &ax3, '+');
					ax3 = vec3_combine_vec(&ray->hitpoint, &ax3, '-');
					ax3 = normalise(ax3);
					if (vec3_dot_product(ax2, ax3) - cos(specs->angle/2 * (M_PI/180)) < NEAR)
						break;
					else if (vec3_dot_product(ax2, ax3) - cos(specs->angle/2 * (M_PI/180)) < -NEAR)
						break;
				}
			}
			ray->hitnormal = ax3;
			ray->plane = 0;
			printf("normal %f %f %f\n",ray->hitnormal.x, ray->hitnormal.y, ray->hitnormal.z);
			//printf("t = %f\n", t1); // we compute closest point on axis and then loop over the axis upward until we find the correct angle through dt product.
		}
	}
	return (1);
}
