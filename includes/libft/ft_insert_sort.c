/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacoman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 18:06:49 by sacoman           #+#    #+#             */
/*   Updated: 2018/07/25 18:29:12 by sacoman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_insert_sort(int *tab, int len)
{
	int i;
	int j;
	int tmp;

	i = 1;
	while (i < len)
	{
		tmp = tab[i];
		j = i - 1;
		while (j >= 0 && tab[j] > tmp)
		{
			tab[j + 1] = tab[j];
			j = j - 1;
		}
		tab[j + 1] = tmp;
		i++;
	}
}
