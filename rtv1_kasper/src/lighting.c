/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 17:46:50 by krutten           #+#    #+#             */
/*   Updated: 2019/10/03 14:01:24 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	ft_abs(double x)
{
	return ((x < 0) ? -x : x);
}

double		ft_max(double a, double b)
{
	return ((a > b) ? a : b);
}

void	intersection_vec3(t_ray *ray)
{
	ray->hitpoint.x = ray->t * ray->direct.x + ray->origin.x;
	ray->hitpoint.y = ray->t * ray->direct.y + ray->origin.y;
	ray->hitpoint.z = ray->t * ray->direct.z + ray->origin.z;
}


int		lighting_distant(t_ray *ray, t_rt *specs, t_ray *shadow_ray, t_obj *l)
{
	t_light_d	*light;

	light = (t_light_d *)l->obj;
//	shadow_ray->direct = vec3_scalar_product(light->direct, -1, '*');
	shadow_ray->direct = light->direct;
	shadow_ray->t = FAR;
	loop_ray_over_objects(shadow_ray, specs);
	if (shadow_ray->t == FAR)
	{
		ray->illum += ft_max(vec3_dot_product(ray->hitnormal, shadow_ray->direct), 0) * light->intensity; //for now assuming white light
		if (ray->illum > 1)
			ray->illum = 1;
	}
	return (0);
}

int		lighting_spherical(t_ray *ray, t_rt *specs, t_ray *shadow_ray, t_obj *l)
{
	t_light_s	*light;
	double		dist;

	light = (t_light_s *)l->obj;
	shadow_ray->direct = vec3_combine_vec(&light->center, &ray->hitpoint, '-');
	shadow_ray->t = sqrt(vec3_dot_product(shadow_ray->direct, shadow_ray->direct));
	shadow_ray->direct = normalise(shadow_ray->direct);
	dist = shadow_ray->t;
	loop_ray_over_objects(shadow_ray, specs);
	if (shadow_ray->t == dist)
	{
		ray->illum += ft_max(vec3_dot_product(ray->hitnormal, shadow_ray->direct), 0) * light->intensity / (dist * dist); //technically 4 * M_PI * radius^2 but since intensity is arbitrary doesnt matter for now assuming white light
		if (ray->illum > 1)
			ray->illum = 1;
	}
	return (0);
}


int		lighting(t_ray *ray, t_rt *specs)
{
	t_ray	shadow_ray;
	t_obj	*l;

	l = specs->light_list;
	intersection_vec3(ray);
	ray->illum = 0.1; // assuming 15% global illumination
	shadow_ray.origin = ray->hitpoint;
	while (l)
	{
		if (l->id == 5)
			lighting_distant(ray, specs, &shadow_ray, l);
		if (l->id == 4)
			lighting_spherical(ray, specs, &shadow_ray, l);
		// light = (t_light *)l->obj;
		// shadow_ray.direct = vec3_combine_vec(&light->center, &ray->hitpoint, '-');
		// shadow_ray.t = sqrt(vec3_dot_product(shadow_ray.direct, shadow_ray.direct));
		// dist = shadow_ray.t;
		// shadow_ray.direct = normalise(shadow_ray.direct);
//		printf("point %f %f %f normal %f %f %f distance %f dot product %f\n", ray->hitpoint.x, ray->hitpoint.y, ray->hitpoint.z, ray->hitnormal.x, ray->hitnormal.y, ray->hitnormal.z, dist, vec3_dot_product(ray->hitnormal, shadow_ray.direct));
		// loop_ray_over_objects(&shadow_ray, specs);
		l = l->next;
	}
// 		if (shadow_ray.t == dist)
// 		{
// 			if (ray->plane == 1)
// 			{
// 				tmp = vec3_combine_vec(&ray->origin, &ray->hitpoint, '-');
// 				double len1 = sqrt(vec3_dot_product(tmp, tmp));
// 				tmp = vec3_scalar_product(ray->hitnormal, 0.05, '*');//consider doing this instead of setting plane variable to 1
// 				tmp = vec3_combine_vec(&ray->hitpoint, &tmp, '+');
// 				tmp = vec3_combine_vec(&ray->origin, &tmp, '-');
// 				double len2 = sqrt(vec3_dot_product(tmp, tmp));
// 				if (len2 > len1)
// 					ray->hitnormal = vec3_scalar_product(ray->hitnormal, -1.0, '*');
// 			}
// 			ray->illum += ft_max(vec3_dot_product(ray->hitnormal, shadow_ray.direct), 0) * light->intensity * 0.5; //for now assuming white light
// 			if (ray->illum > 1)
// 				ray->illum = 1;
// 		}
// 		else
// 		{
// //					printf("point %f %f %f normal %f %f %f distance %f dot product %f\n", ray->hitpoint.x, ray->hitpoint.y, ray->hitpoint.z, ray->hitnormal.x, ray->hitnormal.y, ray->hitnormal.z, dist, vec3_dot_product(ray->hitnormal, shadow_ray.direct));
// //
// //			printf("point %f %f %f at dark side\n", ray->hitpoint.x, ray->hitpoint.y, ray->hitpoint.z);
// 		}
		
// 	}
	return (1); // bullshit return value
}
