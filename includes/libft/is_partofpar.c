/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_partofpar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:24:07 by lutomasz          #+#    #+#             */
/*   Updated: 2019/10/27 16:24:22 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_partofpar(int c)
{
	if (c == ',' || c == ')' || c == '(')
		return (1);
	return (0);
}
