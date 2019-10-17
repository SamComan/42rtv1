/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacoman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 17:51:17 by sacoman           #+#    #+#             */
/*   Updated: 2019/02/07 17:57:40 by sacoman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	put_line(char **tab, char **line, int fd, int ret)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tab[fd][i] != '\n' && tab[fd][i] != '\0')
		i++;
	if (tab[fd][i] == '\n')
	{
		*line = ft_strsub(tab[fd], 0, i);
		tmp = ft_strsub(tab[fd], i + 1, ft_strlen(tab[fd]));
		free(tab[fd]);
		tab[fd] = tmp;
		if (tab[fd][0] == '\0')
			ft_strdel(&tab[fd]);
	}
	else if (tab[fd][i] == '\0')
	{
		if (ret == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(tab[fd]);
		ft_strdel(&tab[fd]);
	}
	return (1);
}

int	ft_read_line(char *buf, char **tab, int fd, char **line)
{
	int		ret;
	char	*tmp;

	ret = 0;
	if ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!tab[fd])
			tab[fd] = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(tab[fd], buf);
			free(tab[fd]);
			tab[fd] = tmp;
		}
		if (!ft_strchr(buf, '\n'))
			return (ft_read_line(buf, tab, fd, line));
	}
	ft_strdel(&buf);
	return (ret);
}

int	get_next_line(const int fd, char **line)
{
	int			ret;
	char		*buf;
	static char	*tab[OPEN_MAX];

	ret = 0;
	if (line == NULL || fd < 0 || BUFF_SIZE <= 0 || fd > OPEN_MAX ||
		(!(buf = ft_strnew(BUFF_SIZE))))
		return (-1);
	if (tab[fd] && ft_strchr(tab[fd], '\n'))
	{
		if (put_line(tab, line, fd, ret))
		{
			ft_strdel(&buf);
			return (1);
		}
	}
	else
		ret = ft_read_line(buf, tab, fd, line);
	if (ret == 0 && (tab[fd] == NULL || tab[fd][0] == '\0'))
		return (0);
	else if (ret == -1)
		return (-1);
	return (put_line(tab, line, fd, ret));
}
