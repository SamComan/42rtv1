/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_combine_vec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:15:56 by krutten           #+#    #+#             */
/*   Updated: 2019/09/30 14:14:49 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_vec3		vec3_combine_vec(t_vec3 *v1, t_vec3 *v2, char c)
{
	int		oper;
	t_vec3	output;

	oper = 1;
	if (c == '-')
		oper = -1;
	if (v2 == NULL)
		return (*v1);
	output.x = v1->x + (oper * v2->x);
	output.y = v1->y + (oper * v2->y);
	output.z = v1->z + (oper * v2->z);
	return (output);
}
