/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 17:04:38 by lutomasz          #+#    #+#             */
/*   Updated: 2019/10/26 17:04:39 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int check_next_char(char **file, int *curr_line, char *c)
{
	++(*curr_line);
	//printf("%s\n", file[*curr_line]);
	while (file[(*curr_line)])
	{
		while (!ft_strstr(file[*curr_line], c) && file[*curr_line])
			++(*curr_line);
		if (*file[*curr_line] != '\n' || *file[*curr_line] != ' ')
		{
			file[*curr_line] = ft_strstr(file[*curr_line], c);
			if ((ft_strncmp((file[*curr_line]), c, 1) != 0))
				++(*curr_line);
			else
				break ;
				
		}
	}
	file[*curr_line] = ft_strstr(file[*curr_line], c);
	if (ft_strncmp((file[*curr_line]), c, 1) != 0)
		return (-1);
	return (1);
}

// camera	 
// {
// 	origin(0, 2, 10)
// 	direction(0, 0, -1)
// }

char  **skip_nonchar_double(char **file, int *curr_line)
{
	int i;

	i = 0;
	++(*curr_line);
	while (file[*curr_line])
	{
		while (file[*curr_line] != '\0')
		{
			if (!(ft_isalpha((int)*file[*curr_line])))
				++file[*curr_line];
			else
			{
				i = 1;
				break ;
			}	
		}
		if (i == 1)
			break ;
		++(*curr_line);
	}
	return (file);
}

int skip_name(char **file, int *curr_line, int len)
{
	file[*curr_line] += len;
	while (*file[*curr_line] == ' ' || *file[*curr_line] == '\t')
		file[*curr_line] += 1;
	if ((ft_isalpha((int)*file[*curr_line])))
		return (-1);
	// printf("%s\n", file[*curr_line]);
	// if (ft_strcmp(file[*curr_line], "(") == 0)
	// 	printf("correct\n");
	--(*curr_line);
	if (check_next_char(file, curr_line, "(") == -1)
		return (-1);
	return (1);
}

int 	check_vector_validity(char *vector)
{
	int i;
	int par;
	int vir;

	par = 0;
	vir = 0;
	i = -1;
	while (vector[++i])
	{
		if (vector[i] == ',' || vector[i] == '(' || vector[i] == ')')
		{
			vector[i] == ',' ? ++vir : 0;
			vector[i] == ')' ? ++par : 0;
			vector[i] == '(' ? ++par : 0;

		}
		if (ft_isalpha(vector[i]))
			return (-1);
	}
	if (par != 2 || vir != 2)
		return (-1);
	return (0);

}

int check_color(char *color)
{
	int par1;
	int par2;
	int err;

	par2 = 0;
	err = 0;
	par1 = 0;
	while (color)
	{
		if (*color == ')' || *color == '(')
		{
			*color == '(' ? ++par1 : 0;
			*color == ')' ? ++par2 : 0;
		}
		if ((!(ft_isdigit(*color))) && (*color < 'a' || *color > 'f') &&
			(*color != '(' && *color != ')') && (*color < 'A' || *color > 'F'))
		{
			err++;
			break ;
		}
		if (*color == ')')
			break ;
		++color;
	}
	if ((par2 != 1 || par1 != 1) || err > 0)
		return  (-1);
	return (1);
}

int find_color(char **file, int *curr_line, char *str)
{
	int len;

	// printf("ligne passée %s\n", file[*curr_line]);
	file = skip_nonchar_double(file, curr_line);
	// printf("Updated position == %s\n", file[*curr_line]);
	len = ft_strlen(str);
	while (file[(*curr_line)])
	{
		if (ft_strncmp(file[*curr_line], str, len) == 0)
			break ;
		else
		{
			//change printf into mine
			printf("%s %s %s %d\n", "should have found", str, "at the line", *curr_line + 1);
			return (-1);
		}
	}
	if (skip_name(file, curr_line, len) == -1)
		return (-1);
	if (check_color(file[*curr_line]) == -1)
	{
		printf("%s %d\n", "incorrect color format at the line", *curr_line + 1);
		return (-1);
	}
	return (1);
}

int check_single_validity(char *vector)
{
	int par1;
	int par2;
	int err;
	int i;

	par2 = 0;
	err = 0;
	par1 = 0;
	i = -1;
	while (vector[++i])
	{
		if (vector[i] == ')' || vector[i] == '(')
		{
			vector[i] == '(' ? ++par1 : 0;
			vector[i] == ')' ? ++par2 : 0;
		}
		if ((!(ft_isdigit(vector[i]))) && !is_partofpar(vector[i]) && vector[i] != '.')
		{
			err++;
			break ;
		}
		if (vector[i] == ')')
			break ;
	}
	if ((par2 != 1 || par1 != 1) || err > 0)
		return  (-1);
	++vector;
	return (1);
}

double get_single_value(char *str)
{
	return (ft_atof(++str));
}

int find_vec(char **file, int *curr_line, char *str, int id)
{
	int len;

	// printf("ligne passée %s\n", file[*curr_line]);
	file = skip_nonchar_double(file, curr_line);
	// printf("Updated position == %s\n", file[*curr_line]);
	len = ft_strlen(str);
	while (file[(*curr_line)])
	{
		if (ft_strncmp(file[*curr_line], str, len) == 0)
			break ;
		else
		{
			//change printf into mine
			printf("%s %s %s %d\n", "should have found", str, "at the line", *curr_line + 1);
			return (-1);
		}
	}
	if (skip_name(file, curr_line, len) == -1)
		return (-1);
	if (id != 1 && check_vector_validity(file[*curr_line]) == -1)
	{
		printf("%s %d\n", "incorrect vector format at the line", *curr_line + 1);
		return (-1);
	}	
	if (id == 1)
		if (check_single_validity(file[*curr_line]) == -1)
			return (-1);
	return (1);
}



int get_color_value(char *vector)
{
	int color;

	++vector;
	color = ft_atoi_base(vector, 16);
	return (1);
}

int get_vector_value(char *vector)
{
	double x;
	double y;
	double z;

	x = ft_atof(vector);
	while (ft_is_space(vector[0]) || is_partofpar(vector[0]))
		++vector;
	while (ft_isdigit(vector[0]) || vector[0] == '.')
		++vector;
	y = ft_atof(vector);
	while (ft_is_space(vector[0]) || is_partofpar(vector[0]))
		++vector;
	while (ft_isdigit(vector[0]) || vector[0] == '.')
		++vector;
	z = ft_atof(vector);
	// printf("%f\n", x);
	// printf("%f\n", y);
	// printf("%f\n", z);
	return (1);
}


