/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacoman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:15:17 by sacoman           #+#    #+#             */
/*   Updated: 2019/10/12 17:20:21 by sacoman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec4	create_vector(int x, int y, int z)
{
	t_vec4	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	vec.w = 1;

	return (vec);

}

t_camera	create_camera(t_vec4 position, t_vec4 lookat, double fl)
{
	t_camera	camera;
	t_vec4		forward;
	t_vec4		world_up;

	camera.position = position;
	camera.lookat = lookat;
	world_up = create_vector(0, 1 0);

	forward = normalize(vector_sub(camera.lookat, camera.position));
	camera.left = normalize(cross_product(world_up, forward));
	camera.up = normalize(cross_product(forward, camera.left));
	camera.forward = forward;

	camera.focal_length = fl;
	camera.frame_height = 1;
	camera.frame_width = 1;

	return (camera);
}

void	rt_logic()
{
	

}
