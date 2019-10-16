/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 13:57:28 by krutten           #+#    #+#             */
/*   Updated: 2019/10/04 16:51:36 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "../includes/minilibx_macos/mlx.h"
# include "../includes/libft/libft.h"
# define FAR 1000000
# define NEAR 0.0001
# define WIDTH 800
# define HEIGHT 800
# define W_IMG  800
# define H_IMG	800
# define ABS(x) ((x) < 0 ? -(x): (x))
# define RIGHT 123
# define LEFT 124
# define UP 125
# define DOWN 126
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
typedef struct		s_ray
{
	t_vec3			origin;
	t_vec3			direct;
	int				near_col;
	double			t;
	t_vec3			hitpoint;
	t_vec3			hitnormal;
	double			illum;
//	int				plane;
}					t_ray;

typedef struct		s_obj
{
	void			*obj;
	int				id; // 0 plane 1 sphere 2 cylinder 3 cone 4 spherical light 5 distant light
	struct s_obj	*next;
}					t_obj;

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
	int				(*fct_ptr[4])(t_ray *, void *);
}					t_rt;

typedef struct		s_light_s
{
	t_vec3			center;
	double			radius;
	int				color;
	double			intensity;
}					t_light_s;

typedef struct		s_light_d
{
	t_vec3			direct;
	double			radius;
	int				color;
	double			intensity;
}					t_light_d;

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

/*
** PARSING
*/

void				parse(t_rt *specs);
int					advance(char *str);
char				*move(int *i, int *j, t_rt *specs);
void				starter(int *i, int *j, t_rt *specs);
void				parse_objects(int *i, t_rt *specs);
t_obj				*new_object(void *inf, int id);
void				add_object(t_obj **list, t_obj *new);
void				free_obj_list(t_obj **list, char *str);
void				free_all_lists(t_rt *specs);
void				parse_vec(t_vec3 *ptr, int *i, int *j, t_rt *specs);
void				parse_vec_spec(t_vec3 *ptr, int *i, int *j, t_rt *specs);

/*
** TECHNICAL
*/

int					intersect(t_ray ray);
int					sphere_intersect(t_ray *ray, void *hit_object);
int					plane_intersect(t_ray *ray, void *hit_object);
int					cone_intersect(t_ray *ray, void *hit_object);
int					deal_key(int key, t_rt *specs);
int					cylinder_intersect(t_ray *ray, void *hit_object);
t_mat3				rot_from_base(t_vec3 view, t_vec3 base, int wrong);
t_vec3				normalise(t_vec3 v1);
void				loop_ray_over_objects(t_ray *ray, t_rt *specs);
int					lighting(t_ray *ray, t_rt *specs);
void				intersection_vec3(t_ray *ray);
t_vec3				pixel_to_world(float x, float y, t_rt *specs);
int					cap_intersect_top(t_ray *ray, t_cyl *specs);
int					cap_intersect_bot(t_ray *ray, t_cyl *specs);

int					cone_cap_intersect_bot(t_ray *ray, t_cone *specs);
int					cone_cap_intersect_top(t_ray *ray, t_cone *specs);
void				draw_image(t_rt *specs);

void				parse_lights_s(int *i, t_rt *specs);
void				parse_lights_d(int *i, t_rt *specs);
void				normal_towards_cam(t_ray *ray);
#endif
