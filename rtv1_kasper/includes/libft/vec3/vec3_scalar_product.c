/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_scalar_product.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 15:44:08 by krutten           #+#    #+#             */
/*   Updated: 2019/09/30 14:17:42 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_vec3		vec3_scalar_product(t_vec3 v1, double c, char a)
{
	t_vec3	output;
	double	scalar;

	scalar = c;
	if (a == '/' && c != 0)
		scalar = 1 / scalar;
	output.x = v1.x * scalar;
	output.y = v1.y * scalar;
	output.z = v1.z * scalar;
	return (output);
}
