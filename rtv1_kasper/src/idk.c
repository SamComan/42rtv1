
t_ray	get_shadow_ray(t_ray *ray, t_vec3 *l_origin)
{
	t_ray	shadow_ray;

	intersection_vec3(ray);
	shadow_ray.origin = ray->hitpoint;
	shadow_ray.direct = normalise(vec3_combine_vec(l_origin,
	&shadow_ray.origin, '-'));
	return (shadow_ray);
}

// void	ray_inter_lights(t_rt *specs, t_vec3 normal, t_ray *ray,
// 			t_vec3 diffuse_kd, double specular_ks)
// {
// 	t_var		v;
// 	t_ray		shadow_ray;
// 	t_shader	sha;
// 	t_obj		*lights;
// 	t_light		*light;
// 	double		n_dot_l;
// 	double		dist;
// 	t_vec3		V;
// 	t_vec3		R;
// 	t_vec3		vec;
// 	double		tmp;

// 	lights = specs->light_list;
// 	sha.diff = create_vector(0.0, 0.0, 0.0);
// 	sha.spec = create_vector(0.0, 0.0, 0.0);
// 	while (lights)
// 	{
// 		light = (t_light *)lights->obj;
// 		shadow_ray = get_shadow_ray(ray, &light->center);
// 		n_dot_l = ft_max(vec3_dot_product(shadow_ray.direct, normal), 0);
// 		dist = shadow_ray.t;
// 		loop_ray_over_objects(&shadow_ray, specs);
// 		if (shadow_ray.t == dist)
// 		{
// 			sha.diff.x = n_dot_l * diffuse_kd.x * light->intensity;
// 			sha.diff.y = n_dot_l * diffuse_kd.y * light->intensity;
// 			sha.diff.z = n_dot_l * diffuse_kd.z * light->intensity;
// 			if (n_dot_l == 0)
// 				tmp = 0;
// 			else
// 			{
// 				V = vec3_scalar_product(ray->direct, -1, '*');
// 				vec = vec3_scalar_product(normal, 2 * n_dot_l, '*');
// 				R = vec3_combine_vec(&vec, &shadow_ray.direct, '-');
// 				tmp = pow(ft_max(vec3_dot_product(R, V), 0), SPECULAR_POW);
// 			}
// 			sha.spec.x += tmp * specular_ks * light->intensity;
// 			sha.spec.y += tmp * specular_ks * light->intensity;
// 			sha.spec.z += tmp * specular_ks * light->intensity;
// 			printf("sha.diff.x = %f, sha.diff.y = %f, sha.diff.z = %f, sha.spec.x = %f, sha.spec.y = %f, sha.spec.z = %f\n",
// 			sha.diff.x, sha.diff.y, sha.diff.z, sha.spec.x, sha.spec.y, sha.spec.z);
// 		}
// 		v.red = ((ray->near_col >> 16) & 0xff) * sha.diff.x + sha.spec.x * ((light->color >> 16) & 0xff) + AMBIANT * ((ray->near_col >> 16) & 0xff);
// 		v.green = ((ray->near_col >> 8) & 0xff) * sha.diff.y + sha.spec.y * ((light->color >> 8) & 0xff) + AMBIANT * ((ray->near_col >> 8) & 0xff);
// 		v.blue = (ray->near_col & 0xff) * sha.diff.z + sha.spec.z * (light->color & 0xff) + AMBIANT * (ray->near_col & 0xff);
// 		ray->near_col = (v.red << 16) | (v.green << 8) | v.blue;
// 		lights = lights->next;
// 	}
// }