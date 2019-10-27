/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:16:10 by lutomasz          #+#    #+#             */
/*   Updated: 2019/10/27 16:16:19 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		after_point(long double nb, const char *str)
{
	int		i;
	double	base;

	i = 0;
	base = 0.1;
	if (str[i++] == '.')
	{
		while (ft_isdigit(str[i]))
		{
			nb += ((str[i] - '0') * base);
			base /= 10;
			i++;
		}
	}
	return ((double)nb);
}

double		ft_atof(const char *str)
{
	long double		nb;
	int				i;
	int				signe;

	i = 0;
	nb = 0.0;
	signe = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == ' ' ||
			str[i] == ',' || str[i] == '(')
		i++;
	if (str[i] == '-')
		signe = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		if (nb > 9223372036854775807)
			return (signe == -1 ? 0 : -1);
		nb = nb * 10;
		nb = nb + (str[i] - '0');
		i++;
	}
	return ((after_point(nb, &str[i]) * signe));
}
