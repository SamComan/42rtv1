/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacoman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 19:41:27 by sacoman           #+#    #+#             */
/*   Updated: 2018/07/24 21:32:50 by sacoman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long		get_length(int nb)
{
	long	len;

	if (nb == 0)
		return (1);
	len = 0;
	if (nb < 0)
	{
		len++;
		nb = -nb;
	}
	while (nb != 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len++);
}

char			*ft_itoa(int n)
{
	long	nb;
	long	len;
	char	*new;

	nb = n;
	len = get_length(nb);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	new[len] = '\0';
	len--;
	if (nb < 0)
		nb = -nb;
	while (len >= 0)
	{
		new[len] = (nb % 10) + '0';
		len--;
		nb = nb / 10;
	}
	if (n < 0)
		new[0] = '-';
	return (new);
}
