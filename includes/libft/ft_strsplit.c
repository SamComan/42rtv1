/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacoman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 21:30:37 by sacoman           #+#    #+#             */
/*   Updated: 2018/07/23 19:58:49 by sacoman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		find_nb_words(char *s, char c)
{
	int is_word;
	int i;

	i = 0;
	is_word = 0;
	while (*s)
	{
		if (is_word == 0 && *s != c)
		{
			is_word = 1;
			i++;
		}
		else if (is_word == 1 && *s == c)
			is_word = 0;
		s++;
	}
	return (i);
}

static int		find_str_end(char *s, char c)
{
	int ln;

	ln = 0;
	while (*s != c && *s)
	{
		ln++;
		s++;
	}
	return (ln);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		nb_words;
	int		i;

	if (s)
	{
		nb_words = find_nb_words((char *)s, c);
		tab = (char**)malloc(sizeof(*tab) * (nb_words + 1));
		if (!tab)
			return (NULL);
		i = 0;
		while (i < nb_words)
		{
			while (*s && *s == c)
				s++;
			tab[i] = ft_strsub((char *)s, 0, find_str_end((char *)s, c));
			if (!tab[i])
				return (NULL);
			s = s + find_str_end((char *)s, c);
			i++;
		}
		tab[i] = NULL;
		return (tab);
	}
	return (NULL);
}
