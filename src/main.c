#include "rtv1.h"
/**
 * DONE
 */
t_vec3  norm(t_vec3 v)
{
    float   length;
    t_vec3  norm_v;

    length = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
    norm_v.x = v.x / length;
    norm_v.y = v.y / length;
    norm_v.z = v.z / length;
    return (norm_v);
}

t_obj		*new_object(void *inf, int id)
{
	t_obj *new;

	if (!(new = (t_obj *)malloc(sizeof(*new))))
		return (NULL);
	new->obj = inf;
	new->id = id;
	new->next = NULL;
	return (new);
}

void		add_object(t_obj **list, t_obj *new)
{
	if (!*list && new)
	{
		*list = new;
		return ;
	}
	if (*list && new)
	{
		new->next = *list;
		*list = new;
	}
}

void	intersection_vec3(t_ray *ray)
{
	ray->hitpoint.x = ray->t * ray->direct.x + ray->origin.x;
	ray->hitpoint.y = ray->t * ray->direct.y + ray->origin.y;
	ray->hitpoint.z = ray->t * ray->direct.z + ray->origin.z;
}


t_vec3		vec3_combine_vec(t_vec3 *v1, t_vec3 *v2, char c)
{
	int		oper;
	t_vec3	output;

	oper = 1;
	if (c == '-')
		oper = -1;
	if (v2 == NULL)
		return (*v1);
	output.x = v1->x + (oper * v2->x);
	output.y = v1->y + (oper * v2->y);
	output.z = v1->z + (oper * v2->z);
	return (output);
}

double	vec3_dot_product(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

void	sphere_inter2(t_ray *ray, t_var *v)
{
	if (v->t2 < v->t1 && v->t2 > 0)
		v->t1 = v->t2;
	if (v->t1 < ray->t)
	{
		ray->near_col = v->s->color;
		ray->t = v->t1;
		intersection_vec3(ray);
		ray->hitnormal = norm(vec3_combine_vec(&ray->hitpoint,
		&v->s->center, '-'));
	}
}

int		sphere_intersect(t_ray *ray, void *ptr)
{
	t_var v;

	v.s = (t_sphere *)ptr;
	v.oc = vec3_combine_vec(&ray->origin, &v.s->center, '-');
	v.ext = vec3_combine_vec(&ray->origin, &ray->direct, '+');
	v.ext = vec3_combine_vec(&v.ext, &v.s->center, '-');
	if (vec3_dot_product(v.ext, v.ext) > vec3_dot_product(v.oc, v.oc))
		return (0);
	v.b = 2 * vec3_dot_product(ray->direct, v.oc);
	v.c = vec3_dot_product(v.oc, v.oc) - (v.s->radius * v.s->radius);
	v.d = v.b * v.b - 4 * v.c;
	if (v.d < 0)
		return (0);
	v.t1 = (-v.b + sqrt(v.d)) / 2;
	v.t2 = (-v.b - sqrt(v.d)) / 2;
	sphere_inter2(ray, &v);
	return (1);
}

void		init_rt_struct(t_rt *specs)
{
    t_sphere    *sph;
    t_obj       *new;
    t_obj       *objects;


printf("BEFORE SPHERE");
    sph = (t_sphere *)malloc(sizeof(*sph));
    //if (!(
        specs->mlx = mlx_init();
	//	return (0);


    specs->ft_ptr[0] = sphere_intersect;
	specs->ft_ptr[1] = sphere_intersect;
	specs->ft_ptr[2] = sphere_intersect;
	specs->ft_ptr[3] = sphere_intersect;

    specs->win = mlx_new_window(specs->mlx, WIN_WIDTH, WIN_HEIGHT, "rtv1");
    specs->aspect = WIN_HEIGHT / WIN_WIDTH;
    //specs->obj_list = NULL;
    specs->camera.x = 0.00;
    specs->camera.y = 0.00;
    specs->camera.z = 10.00;
    //specs->camera = norm(specs->camera);
    specs->view_dir.x = 0.3;
    specs->view_dir.y = 0.00;
    specs->view_dir.z = -1.00;
    specs->view_dir = norm(specs->view_dir);
    sph->center.x = 0.00;
    sph->center.y = 0.00;
    sph->center.z = 0.00;
    sph->color = 0x54a4c4;
    sph->radius = 3.00;
    new = new_object(sph, 1);
    add_object(&specs->obj_list, new);

printf("BEFORE OBJ LOOP");

printf(" \n CAMERA \n camera position x = %f, y = %f, z = %f \n camera direction x = %f, y = %f, z = %f\n",
	specs->camera.x, specs->camera.y,  specs->camera.z, specs->view_dir.x, specs->view_dir.y, specs->view_dir.z);
    objects = specs->obj_list;
    
    while(objects)
    {
        if (objects->id == 1)
        {
        printf(" \n SPHERE \n center x = %f y = %f z = %f, radius = %f, color = %d\n", ((t_sphere *)objects->obj)->center.x, ((t_sphere *)objects->obj)->center.y, ((t_sphere *)objects->obj)->center.z, ((t_sphere *)objects->obj)->radius, ((t_sphere *)objects->obj)->color);
        }
        objects = objects->next;
    }

    printf("AFTER OBJ LOOP");


}

/**
 * DONE
 */
void    intersect_object(t_ray *ray, t_rt *specs)
{
    t_obj   *o;

    o = specs->obj_list;
    //printf("BEFORE WHILE INTERSECT\n");
    while (o)
    {
        
        specs->ft_ptr[o->id](ray, o->obj);
        //printf("AFTER FT\n");
        o = o->next;
    }

}

/**
 * ALMOST DONE WITHOUT ROTATION FROM BASE
 */
t_vec3 raster_to_world(float x, float y, t_rt *specs)
{
    t_vec3	ray;

	ray.x = ((2.0 * x) - 1.0) * tan(specs->alpha / 2.0) * specs->aspect;
	ray.y = (1.0 - (2.0 * y)) * tan(specs->alpha / 2.0);
	ray.z = -1.0;
    ray = norm(ray);
    return (ray);
}


/**
 * .....
 */
int     trace_ray(float x, float y, t_rt *specs)
{
    t_var   v;
    t_ray   ray;
    t_obj   *o;

    o = specs->obj_list;
    ray.origin = specs->camera;
    ray.direct = raster_to_world(x, y, specs);
    ray.direct = norm(ray.direct);
    ray.t = FAR;
    ray.near_col = 0x88;
    //printf("BEFORE INTERSECT\n");
    intersect_object(&ray, specs);
    //printf("AFTER INTERSECT\n");
    if (ray.t < FAR)
    {
        v.red = ((ray.near_col >> 16) & 0xff);
        v.green = ((ray.near_col >> 8) & 0xff);
        v.blue = (ray.near_col & 0xff);
        ray.near_col = (v.red << 16) | (v.green << 8) | v.blue;
        return (ray.near_col);
    }
    return (-1);
}

/**
 * DONE 
 */ 
void    color_pixel(int color, int x, int y, t_rt *specs)
{
    specs->img_str[(y * WIN_WIDTH + x) * 4] = color & 0xff;
    specs->img_str[(y * WIN_WIDTH + x) * 4 + 1] = (color >> 8) & 0xff;
    specs->img_str[(y * WIN_WIDTH + x) * 4 + 2] = (color >> 16) & 0xff;
}

/**
* DONE
*/
int    loop_on_pixel(t_rt *specs)
{
    int color;
    int x;
    int y;

    y = 0;
    while(y < WIN_HEIGHT)
    {
        x = 0;
        while(x < WIN_WIDTH)
        {
            //printf("BEFORE TRACE PIXEL\n");
            if((color = trace_ray((float)x / WIN_WIDTH, (float)y / WIN_HEIGHT, specs)) != -1)
            {
                //printf("BEFORE  COLOR PIXEL\n");
                color_pixel(color, x, y, specs);
            }
            else
                specs->img_str[(y * WIN_WIDTH + x) * 4] = '0';
            x++;
        }
        y++;
    }
    return (0);


    
}

/**
 * DONE
 */
void		draw_image(t_rt *specs)
{
	specs->img = mlx_new_image(specs->mlx, WIN_WIDTH, WIN_HEIGHT);
	specs->img_str = mlx_get_data_addr(specs->img, &specs->bpp,
	&specs->size_line, &specs->endian);
    //printf("BEFORE LOOP PIXEL\n");
	loop_on_pixel(specs);
    //printf("AFTER LOOP PIXEL\n");
	mlx_put_image_to_window(specs->mlx, specs->win, specs->img, 0, 0);
	mlx_destroy_image(specs->mlx, specs->img);
}

int     deal_key(int key, t_rt *specs)
{
    if (key == 53)
	{
		//free_all_lists(specs);
		exit(0);
	}
    draw_image(specs);
    return (0);
}

/**
* ALMOST DONE
*/
int			main()
{
	t_rt		specs;
	//int			fd;

	// if (ac != 2)
	// {
	// 	ft_putstr("Usage: ./rtv1 scenefile\n");
	// 	return (0);
	// }
	// if ((fd = open(av[1], O_RDONLY)) < 0)
	// {
	// 	perror("");
	// 	return (0);
	// }
	//if (!init_rt_struct(fd, &specs))
	// {
	// 	ft_putstr_fd("Failed to read input file\n", 2);
	// 	return (0);
	// }
//printf("BEFORE INIT\n");
    init_rt_struct(&specs);
    //parsing();
    specs.view_dir = norm(specs.view_dir);
    //printf("BEFORE DRAW\n");
    draw_image(&specs);
    //printf("AFTER DRAW\n");
	mlx_key_hook(specs.win, deal_key, &specs);
	mlx_loop(specs.mlx);
	return (0);
}