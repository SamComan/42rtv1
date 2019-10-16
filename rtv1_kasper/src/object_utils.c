/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:57:47 by rkamegne          #+#    #+#             */
/*   Updated: 2019/09/30 16:54:13 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		advance(char *str)
{
	int		i;

	i = 0;
	while (str[i] != ',')
		i++;
	return (++i);
}

char	*move(int *i, int *j, t_rt *specs)
{
	(*i)++;
	*j = 0;
	while (specs->input[*i][*j] != '(')
		(*j)++;
	return (&specs->input[*i][++(*j)]);
}

void	starter(int *i, int *j, t_rt *specs)
{
	*j = 0;
	(*i) += 2;
	while (specs->input[*i][*j] != '(')
		(*j)++;
	(*j)++;
}

void	parse_vec(t_vec3 *ptr, int *i, int *j, t_rt *specs)
{
	ptr->x = ft_atof(&specs->input[*i][*j]);
	*j += advance(&specs->input[*i][*j]);
	ptr->y = ft_atof(&specs->input[*i][*j]);
	*j += advance(&specs->input[*i][*j]);
	ptr->z = ft_atof(&specs->input[*i][*j]);
}

void	parse_vec_spec(t_vec3 *ptr, int *i, int *j, t_rt *specs)
{
	ptr->x = ft_atof(move(i, j, specs));
	*j += advance(&specs->input[*i][*j]);
	ptr->y = ft_atof(&specs->input[*i][*j]);
	*j += advance(&specs->input[*i][*j]);
	ptr->z = ft_atof(&specs->input[*i][*j]);
	*ptr = normalise(*ptr);
}
