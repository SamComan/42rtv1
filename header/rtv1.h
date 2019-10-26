/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacoman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:56:39 by sacoman           #+#    #+#             */
/*   Updated: 2019/10/12 17:10:14 by sacoman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _RT_H_
# define _RT_H_
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "../includes/minilibx_macos/mlx.h"
# include "../includes/libft/libft.h"
# include "../includes/libft/get_next_line.h"
# include "math.h"
# define FAR 1000000
# define NEAR 0.0001
# define WIN_HEIGHT 800
# define WIN_WIDTH 800
# define ABS(x) ((x) < 0 ? -(x): (x))

typedef	struct	s_list_rt
{
	char				**str;
	struct s_list_rt	*next;
}				t_list_rt;

typedef struct		s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct		s_mat3
{
	double			m[3][3];
}					t_mat3;

typedef struct		s_plane
{
	t_vec3			point;
	t_vec3			normal;
	int				color;
}					t_plane;

typedef struct		s_sphere
{
	t_vec3			center;
	double			radius;
	int				color;
}					t_sphere;

typedef struct		s_cyl
{
	t_vec3			center;
	t_vec3			axis;
	double			max;
	double			radius;
	int				color;
	t_mat3			rot;
	t_mat3			trans;
	t_mat3			scale;
	t_mat3			scale_inv;
	t_mat3			rot_inv;
	int				computed;
}					t_cyl;

typedef struct		s_cone
{
	t_vec3			center;
	double			height;
	t_vec3			axis;
	double			min;
	double			max;
	double			angle;
	int				color;
	t_mat3			rot;
	t_mat3			trans;
	t_mat3			scale;
	t_mat3			scale_inv;
	t_mat3			rot_inv;
	int				computed;
}					t_cone;

typedef struct		s_light
{
	t_vec3			direct;
	double			radius;
	int				color;
	double			intensity;
}					t_light;

typedef struct		s_obj
{
	void			*obj;
	int				id; // 0 plane 1 sphere 2 cylinder 3 cone 4 spherical light 5 distant light
	struct s_obj	*next;
}					t_obj;

typedef struct		s_ray
{
	t_vec3			origin;
	t_vec3			direct;
	int				near_col;
	double			t;
	t_vec3			hitpoint;
	t_vec3			hitnormal;
	double			illum;
	int				plane;
}					t_ray;

typedef struct		s_rt
{
	int				first;
	void			*mlx;
	void			*win;
	void			*img;
	int				bpp;
	int				size_line;
	int				endian;
	t_vec3			camera;
	t_vec3			view_dir;
	t_mat3			view_rot;
	double			alpha;
	double			aspect;
	char			**input;
	char			*img_str;
	t_obj			*obj_list;
	t_obj			*light_list;
	int				(*ft_ptr[4])(t_ray *, void *);
}					t_rt;

typedef struct		s_var
{
	int				red;
	int				green;
	int				blue;
	double			a;
	double			b;
	double			c;
	t_vec3			oc;
	double			d;
	double			t1;
	double			t2;
	t_sphere		*s;
	t_vec3			ext;
}					t_var;


int     deal_key(int key, t_rt *specs);
void		draw_image(t_rt *specs);
int    loop_on_pixel(t_rt *specs);
void    color_pixel(int color, int x, int y, t_rt *specs);
int     trace_ray(float x, float y, t_rt *specs);
int     lighting(t_ray *ray, t_rt *specs);
int     distant_light(t_ray *ray, t_rt *specs, t_ray *shadow_ray, t_obj *lights);
double		ft_max(double a, double b);
double	ft_abs(double x);
t_vec3 raster_to_world(float x, float y, t_rt *specs);
void    intersect_object(t_ray *ray, t_rt *specs);
void		init_rt_struct(t_rt *specs);
int		plane_intersect(t_ray *ray, void *hit_object);
void	normal_towards_cam(t_ray *ray);
int		sphere_intersect(t_ray *ray, void *ptr);
void	sphere_inter2(t_ray *ray, t_var *v);
t_vec3      vec3_scalar_product(t_vec3 v1, double c, char a);
double	vec3_dot_product(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_combine_vec(t_vec3 *v1, t_vec3 *v2, char c);
void	intersection_vec3(t_ray *ray);
void		add_object(t_obj **list, t_obj *new);
t_obj		*new_object(void *inf, int id);
t_vec3  norm(t_vec3 v);

int		cone_intersect(t_ray *ray, void *hit_object);
int		cylinder_intersect(t_ray *ray, void *hit_object);
int		cone_cap_intersect_top(t_ray *ray, t_cone *specs);
int		cone_cap_intersect_bot(t_ray *ray, t_cone *specs);
int		cap_intersect_top(t_ray *ray, t_cyl *specs);
int		cap_intersect_bot(t_ray *ray, t_cyl *specs);

char		**ft_file_read(int fd);

#endif
