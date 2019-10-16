/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:05:20 by rkamegne          #+#    #+#             */
/*   Updated: 2019/10/03 18:14:58 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		deal_key2(int key, t_rt *specs)
{
	if (key == KEY_A)
		specs->view_dir = vector_matrix_multiply(specs->view_dir,
		rotation_matrix_y(1.0));
	if (key == KEY_D)
		specs->view_dir = vector_matrix_multiply(specs->view_dir,
		rotation_matrix_y(-1.0));
	if (key == KEY_W)
		specs->view_dir = vector_matrix_multiply(specs->view_dir,
		rotation_matrix_x(1.0));
	if (key == KEY_S)
		specs->view_dir = vector_matrix_multiply(specs->view_dir,
		rotation_matrix_x(-1.0));
	specs->first = 0;
	return (0);
}

int		deal_key(int key, t_rt *specs)
{
	printf("key pressed = %d\n", key);
	if (key == RIGHT)
		specs->camera.x += 0.25;
	if (key == LEFT)
		specs->camera.x -= 0.25;
	if (key == UP)
		specs->camera.y += 0.25;
	if (key == DOWN)
		specs->camera.y -= 0.25;
	if (key == 53)
	{
		free_all_lists(specs);
		exit(0);
	}
	deal_key2(key, specs);
	draw_image(specs);
	return (0);
}
