/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 15:53:03 by lutomasz          #+#    #+#             */
/*   Updated: 2019/10/25 15:53:07 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "../includes/libft/get_next_line.h"



void		free_tab(void **tab)
{
	while (*tab)
	{
		free(*tab);
		tab++;
	}
	tab = NULL;
}

t_list_rt	*ft_lst_new(char **string)
{
	t_list_rt	*new;

	if (!(new = (t_list_rt *)malloc(sizeof(t_list_rt))))
	{
		free_tab((void **)string);
		return (NULL);
	}
	new->str = string;
	new->next = NULL;
	return (new);
}

void		ft_lst_add_last(t_list_rt **begin_list, t_list_rt *new)
{
	t_list_rt	*tmp;

	if (*begin_list && new)
	{
		tmp = *begin_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static void	free_str(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void		ft_lst_del(t_list_rt **list)
{
	t_list_rt	*next;

	if (*list)
	{
		while ((*list)->next)
		{
			next = (*list)->next;
			free_str((*list)->str);
			free(*list);
			*list = next;
		}
		free(*list);
	}
}

static void	ft_read_handle(t_list_rt **list, char **string)
{
	t_list_rt *new;

	if (!*list)
	{
		if (!(*list = ft_lst_new(string)))
		{
			free_str(string);
			exit(0);
		}
	}
	else
	{
		if (!(new = ft_lst_new(string)))
		{
			free_str(string);
			ft_lst_del(list);
			exit(0);
		}
		ft_lst_add_last(list, new);
	}
}

void	ft_print_tab2(char **tab)
{
	int i;
	int j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			write(1, &tab[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list *next;

	while (lst != NULL && f != NULL)
	{
		next = lst->next;
		f(lst);
		lst = next;
	}
}

void		handle_all(t_list_rt *list, char **string)
{
	free_str(string);
	ft_lst_del(&list);
}

char **get_char_tab2(t_list_rt *list, int size, char **string)
{
	char **tab;
	int i;
	t_list_rt *next;

	if (!(tab = (char**)malloc(sizeof(char*) * size + 1)))
		return (NULL);
	i = -1;
	while (list != NULL && ++i < size)
	{
		next = list->next;
		if (!(tab[i] = ft_strdup(*list->str)))
			return (NULL);
		list = next;
	}
	tab[++i] = 0;
	handle_all(list, string);
	return (tab);
}



char		**ft_file_read(int fd)
{
	int			i;
	char		*line;
	t_list_rt	*list;
	char		**string;
	int ret;

	i = 0;
	list = NULL;
	while ((ret = get_next_line(fd, &line)))
	{
		if (*line < 1)
			return (NULL);
		if (!(string = ft_strsplit(line, '\n')))
			return (NULL);
		ft_read_handle(&list, string);
		i++;
		if (ret == -1)
			break;
	}
	return (get_char_tab2(list, i, string));
}

