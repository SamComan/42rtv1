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

t_vec3      vec3_scalar_product(t_vec3 v1, double c, char a)
{
    t_vec3  output;
    double  scalar;

    scalar = c;
    if (a == '/' && c != 0)
        scalar = 1 / scalar;
    output.x = v1.x * scalar;
    output.y = v1.y * scalar;
    output.z = v1.z * scalar;
    return (output);
}



int		cap_intersect_bot(t_ray *ray, t_cyl *specs)
{
	t_vec3	oc;
	double	t;
	t_plane	p;
	double	dist;

	p.point = specs->center;
	p.normal = specs->axis;
	p.color = specs->color;
	oc = vec3_combine_vec(&ray->origin, &p.point, '-');
	if (vec3_dot_product(ray->direct, p.normal) == 0)
		return (0);
	t = (vec3_dot_product(oc, p.normal) * (-1))
		/ vec3_dot_product(ray->direct, p.normal);
	oc.x = ray->origin.x + t * ray->direct.x;
	oc.y = ray->origin.y + t * ray->direct.y;
	oc.z = ray->origin.z + t * ray->direct.z;
	dist = sqrt(pow(oc.x - p.point.x, 2) + pow(oc.y - p.point.y, 2) + pow(oc.z - p.point.z, 2));
	if (t < ray->t && t > NEAR && dist < specs->radius)
	{
		ray->t = t;
		ray->near_col = p.color;
		ray->hitnormal = p.normal;
		normal_towards_cam(ray);
		return (1);
	}
	return (0);
}

int		cap_intersect_top(t_ray *ray, t_cyl *specs)
{
	t_vec3	oc;
	double	t;
	t_plane	p;
	double	dist;

	p.point = vec3_scalar_product(specs->axis, specs->max, '*');
	p.point = vec3_combine_vec(&specs->center, &p.point, '+');
	p.normal = specs->axis;
	p.color = specs->color;
	oc = vec3_combine_vec(&ray->origin, &p.point, '-');
	if (vec3_dot_product(ray->direct, p.normal) == 0)
		return (0);
	t = (vec3_dot_product(oc, p.normal) * (-1))
		/ vec3_dot_product(ray->direct, p.normal);
	oc.x = ray->origin.x + t * ray->direct.x;
	oc.y = ray->origin.y + t * ray->direct.y;
	oc.z = ray->origin.z + t * ray->direct.z;
	dist = sqrt(pow(oc.x - p.point.x, 2) + pow(oc.y - p.point.y, 2) + pow(oc.z - p.point.z, 2));
	if (t < ray->t && t > NEAR && dist < specs->radius)
	{
		ray->t = t;
		ray->near_col = p.color;
		ray->hitnormal = p.normal;
		normal_towards_cam(ray);
		return (1);
	}
	return (0);
}

int		cone_cap_intersect_bot(t_ray *ray, t_cone *specs)
{
	t_vec3	oc;
	double	t;
	t_plane	p;
	double	dist;
	double	rad;

	p.point = vec3_scalar_product(specs->axis, specs->min, '*');
	p.point = vec3_combine_vec(&specs->center, &p.point, '+');
	p.normal = specs->axis;
	p.color = specs->color;
	oc = vec3_combine_vec(&ray->origin, &p.point, '-');
	if (vec3_dot_product(ray->direct, p.normal) == 0)
		return (0);
	t = (vec3_dot_product(oc, p.normal) * (-1))
		/ vec3_dot_product(ray->direct, p.normal);
	oc.x = ray->origin.x + t * ray->direct.x;
	oc.y = ray->origin.y + t * ray->direct.y;
	oc.z = ray->origin.z + t * ray->direct.z;
	dist = sqrt(pow(oc.x - p.point.x, 2) + pow(oc.y - p.point.y, 2) + pow(oc.z - p.point.z, 2));
	rad = tan(specs->angle) * ABS(specs->min);
	if (t < ray->t && t > NEAR && dist < rad)
	{
		ray->t = t;
		ray->near_col = p.color;
		ray->hitnormal = p.normal;
		normal_towards_cam(ray);
		return (1);
	}
	return (0);
}

int		cone_cap_intersect_top(t_ray *ray, t_cone *specs)
{
	t_vec3	oc;
	double	t;
	t_plane	p;
	double	dist;
	double	rad;

	p.point = vec3_scalar_product(specs->axis, specs->max, '*');
	p.point = vec3_combine_vec(&specs->center, &p.point, '+');
	p.normal = specs->axis;
	p.color = specs->color;
	oc = vec3_combine_vec(&ray->origin, &p.point, '-');
	if (vec3_dot_product(ray->direct, p.normal) == 0)
		return (0);
	t = (vec3_dot_product(oc, p.normal) * (-1))
		/ vec3_dot_product(ray->direct, p.normal);
	oc.x = ray->origin.x + t * ray->direct.x;
	oc.y = ray->origin.y + t * ray->direct.y;
	oc.z = ray->origin.z + t * ray->direct.z;
	dist = sqrt(pow(oc.x - p.point.x, 2) + pow(oc.y - p.point.y, 2) + pow(oc.z - p.point.z, 2));
	rad = tan(specs->angle) * ABS(specs->max);
	if (t < ray->t && t > NEAR && dist < rad)
	{
		ray->t = t;
		ray->near_col = p.color;
		ray->hitnormal = p.normal;
		normal_towards_cam(ray);
		return (1);
	}
	return (0);
}

int		cylinder_intersect(t_ray *ray, void *hit_object)
{
	double	a;
	double	b;
	double	c;
	t_vec3	oc;
	double	d;
	double	t1;
	double	t2;
    t_cyl	*specs;
	t_vec3	p1;
	t_vec3	p2;
	t_vec3	h1;
	t_vec3	h2;
	double	height1;
	double	height2;
	t_vec3	tmp;
	t_vec3	tmp2;
    static int	first_entry;


	specs = (t_cyl *)hit_object;
	if (!first_entry)
		printf("t_cyl: center : %f, %f, %f \taxis: %f, %f, %f \n", specs->center.x, specs->center.y, specs->center.z, specs->axis.x, specs->axis.y, specs->axis.z );
	oc = vec3_combine_vec(&ray->origin, &specs->center, '-');
	if (!first_entry)
		printf("oc = %f, %f, %f\n", oc.x, oc.y, oc.z);
	a = 1 - (vec3_dot_product(ray->direct, specs->axis) * vec3_dot_product(ray->direct, specs->axis)); // D|D - (D|V)^2

	b = 2 * (vec3_dot_product(ray->direct, oc) - (vec3_dot_product(ray->direct, specs->axis) * vec3_dot_product(oc, specs->axis)));  // 2* (D|X - (D|V)*(X|V))
	c = vec3_dot_product(oc, oc) - (vec3_dot_product(oc, specs->axis) * vec3_dot_product(oc, specs->axis)) - (specs->radius * specs->radius); //X|X - (X|V)^2 - r*r
	d = b * b - 4 * a * c;
	if (!first_entry)
	{
		printf("a = %f, b = %f, c = %f, d  = %f\n", a, b, c, d);
		printf("D|X = %f, X|X = %f, X|V = %f, d  = %f\n", vec3_dot_product(ray->direct, oc), vec3_dot_product(oc, oc), vec3_dot_product(oc, specs->axis), d);
	}
	first_entry = 1;
	if (d < 0)
	{
		return (0);
	}
	t1 = (- b + sqrt(d)) / (2 * a);
	t2 = (- b - sqrt(d)) / (2 * a);

	if (t1 < NEAR && t2 < NEAR)
		return (0);
	p1 = vec3_scalar_product(ray->direct, t1, '*');
	p1 = vec3_combine_vec(&ray->origin, &p1, '+');
	h1 = vec3_combine_vec(&p1, &specs->center, '-');
	if ((height1 = vec3_dot_product(h1, specs->axis)) > specs->max || height1 < 0)
	{
		t1 = FAR;

	}
	p2 = vec3_scalar_product(ray->direct, t2, '*');
	p2 = vec3_combine_vec(&ray->origin, &p2, '+');
	h2 = vec3_combine_vec(&p2, &specs->center, '-');
	if ((height2 = vec3_dot_product(h2, specs->axis)) > specs->max || height2 < 0)
	{

		t2 = FAR;
	}
	if (t2 < t1 && t2 > NEAR)
	{
		t1 = t2;
		p1 = p2;
		height1 = height2;

	}
	if (t1 < ray->t && ray->t > NEAR)
	{
		ray->near_col = specs->color;
		ray->t = t1;

		tmp = vec3_scalar_product(specs->axis, height1, '*');
		tmp2 = vec3_combine_vec(&specs->center, &tmp, '+');

		ray->hitnormal = vec3_combine_vec(&p1, &tmp2, '-');
		ray->hitnormal = norm(ray->hitnormal);
    }
	cap_intersect_bot(ray, specs);
	cap_intersect_top(ray, specs);
	return (1);
}

int		cone_intersect(t_ray *ray, void *hit_object)
{
	double	a;
	double	b;
	double	c;
	t_vec3	oc;
	double	d;
	double	t1;
	double	t2;
    t_cone	*specs;
	t_vec3	p1;
	t_vec3	p2;
	t_vec3	h1;
	t_vec3	h2;
	double	height1;
	double	height2;
	t_vec3	tmp;
	t_vec3	tmp2;
	double	hplus;
    double	dist;
    static int	first_entry;


	specs = (t_cone *)hit_object;
	if (!first_entry)
		specs->angle = (specs->angle / 2) * (M_PI/180);
	oc = vec3_combine_vec(&ray->origin, &specs->center, '-');
	if (!first_entry)
		printf("oc = %f, %f, %f\n", oc.x, oc.y, oc.z);
	a = pow(vec3_dot_product(ray->direct, specs->axis), 2) - pow(cos(specs->angle), 2); 
	//(D.V)^2 - cos^2th
	b = 2 * ((vec3_dot_product(ray->direct, specs->axis) * vec3_dot_product(oc, specs->axis)) - (vec3_dot_product(ray->direct, oc) * pow(cos(specs->angle), 2))); 
	// 2* ((D.V)(OC.V)-D.OC*cos^2th)
	c = pow(vec3_dot_product(oc, specs->axis), 2) - (vec3_dot_product(oc, oc) * pow(cos(specs->angle), 2)); 
	d = b * b - 4 * a * c;
	first_entry = 1;
	if (d < 0)
		return (0);
	t1 = (- b + sqrt(d)) / (2 * a);
	t2 = (- b - sqrt(d)) / (2 * a);
	if (t1 < NEAR && t2 < NEAR)
		return (0);
	p1 = vec3_scalar_product(ray->direct, t1, '*');
	p1 = vec3_combine_vec(&ray->origin, &p1, '+');
	h1 = vec3_combine_vec(&p1, &specs->center, '-');
	if ((height1 = vec3_dot_product(h1, specs->axis)) > specs->max || height1 < specs->min)
		t1 = FAR;
	p2 = vec3_scalar_product(ray->direct, t2, '*');
	p2 = vec3_combine_vec(&ray->origin, &p2, '+');
	h2 = vec3_combine_vec(&p2, &specs->center, '-');
	if ((height2 = vec3_dot_product(h2, specs->axis)) > specs->max || height2 < specs->min)
		t2 = FAR;
	if (t2 < t1 && t2 > NEAR)
	{
		t1 = t2;
		p1 = p2;
		height1 = height2;
	}
	if (t1 < ray->t && ray->t > NEAR)
	{
		ray->near_col = specs->color;
		ray->t = t1;
		intersection_vec3(ray);
		tmp = vec3_scalar_product(specs->axis, height1, '*');
		tmp2 = vec3_combine_vec(&specs->center, &tmp, '+');
    	tmp = vec3_combine_vec(&ray->hitpoint, &tmp2, '-');
		dist = sqrt(vec3_dot_product(tmp, tmp));
		hplus = tan(specs->angle) * dist;
		if (height1 > 0)
			height1 += hplus;
		else
			height1 -= hplus;
		tmp = vec3_scalar_product(specs->axis, height1, '*');
		tmp2 = vec3_combine_vec(&specs->center, &tmp, '+');
		ray->hitnormal = vec3_combine_vec(&ray->hitpoint, &tmp2, '-');
		ray->hitnormal = norm(ray->hitnormal);
		cone_cap_intersect_bot(ray, specs);
		cone_cap_intersect_top(ray, specs);
	}
	return (1);
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

void	normal_towards_cam(t_ray *ray)
{
	double	len1;
	double	len2;
	t_vec3	tmp;

	tmp = vec3_combine_vec(&ray->origin, &ray->hitpoint, '-');
	len1 = sqrt(vec3_dot_product(tmp, tmp));
	tmp = vec3_scalar_product(ray->hitnormal, 0.05, '*');//i feel like this could be significantly simpler with an elegant vector product
	tmp = vec3_combine_vec(&ray->hitpoint, &tmp, '+');
	tmp = vec3_combine_vec(&ray->origin, &tmp, '-');
	len2 = sqrt(vec3_dot_product(tmp, tmp));
	if (len2 > len1)
		ray->hitnormal = vec3_scalar_product(ray->hitnormal, -1.0, '*');
}

int		plane_intersect(t_ray *ray, void *hit_object)
{
	t_vec3	oc;
	double	t;
	t_plane	*p;

	p = (t_plane *)hit_object;
	oc = vec3_combine_vec(&ray->origin, &p->point, '-');
	if (vec3_dot_product(ray->direct, p->normal) == 0)
		return (0);
	t = (vec3_dot_product(oc, p->normal) * (-1))
		/ vec3_dot_product(ray->direct, p->normal);
	if (t < ray->t && t > NEAR)
	{
		ray->t = t;
		ray->near_col = p->color;
		ray->hitnormal = p->normal;
		normal_towards_cam(ray);
		return (1);
	}
	return (0);
}

void		init_rt_struct(t_rt *specs)
{
    t_sphere    *sph;
    t_plane     *pl;
    t_cone      *cone;
    t_cyl       *cyl;
    t_obj       *new;
    t_obj       *new2;
    t_obj       *new3;
    // t_obj       *new4;
    // t_obj       *new5;
    t_obj       *objects;
    t_light     *l;


    printf("BEFORE SPHERE");
    sph = (t_sphere *)malloc(sizeof(*sph));
    pl = (t_plane *)malloc(sizeof(*pl));
    cone = (t_cone *)malloc(sizeof(*cone));
    cyl = (t_cyl *)malloc(sizeof(*cyl));
    l = (t_light *)malloc(sizeof(*l));
    //if (!(
        specs->mlx = mlx_init();
	//	return (0);

    l = (t_light *)malloc(sizeof(*l));
    l->direct.x = 10.00;
    l->direct.y = 10.00;
    l->direct.z = 10.00;
    l->direct = norm(l->direct);
    l->radius = 1.00;
    l->color = 0xffffff;
    l->intensity = 0.5;
    new2 = new_object(l, 4);
    add_object(&specs->light_list, new2);

    specs->ft_ptr[0] = plane_intersect;
	specs->ft_ptr[1] = sphere_intersect;
	specs->ft_ptr[2] = cylinder_intersect;
	specs->ft_ptr[3] = cone_intersect;

    specs->win = mlx_new_window(specs->mlx, WIN_WIDTH, WIN_HEIGHT, "rtv1");
    specs->alpha = (90.0 / 180.0) * M_PI;
    specs->aspect = WIN_HEIGHT / WIN_WIDTH;
    //specs->obj_list = NULL;
    specs->camera.x = 0.00;
    specs->camera.y = 0.00;
    specs->camera.z = 10.00;
    //specs->camera = norm(specs->camera);
    specs->view_dir.x = 0.0;
    specs->view_dir.y = 0.00;
    specs->view_dir.z = -1.00;
    specs->view_dir = norm(specs->view_dir);

    //SPHERE
    sph->center.x = 2.00;
    sph->center.y = 0.00;
    sph->center.z = 1.00;
    sph->color = 0xff3838;
    sph->radius = 2.00;
    new = new_object(sph, 1);
    add_object(&specs->obj_list, new);

    //PLANE
    pl->point.x = 0.00;
    pl->point.y = -3.50;
    pl->point.z = 0.00;
    pl->normal.x = 0.00;
    pl->normal.y = 1.00;
    pl->normal.z = 0.00;
    pl->normal = norm(pl->normal);
    pl->color = 0xffffff;
    new3 = new_object(pl, 0);
    add_object(&specs->obj_list, new3);

    //CONE - BULLSHIT
    // cone->center.x = -2.00;
    // cone->center.y = 20.00;
    // cone->center.z = 0.00;
    // cone->axis.x = 1.00;
    // cone->axis.y = 0.00;
    // cone->axis.z = 0.00;
    // cone->axis = norm(cone->axis);
    // cone->height = 1.00;
	// cone->max = 1.00;
	// cone->min = 0.00;
	// cone->angle = 30;
	// cone->color = 0xff3838;
	// cone->computed = 0;
    // new4 = new_object(cone, 0);
    // add_object(&specs->obj_list, new4);

    // //CYLINDRE - ALSO BULLSHIT
    // cyl->center.x = 3.0;
    // cyl->center.y = -4.0;
    // cyl->center.z = -10.0;
    // cyl->axis.x = 0.0;
    // cyl->axis.y = 1.0;
    // cyl->axis.z = 0.0;
    // cyl->max = 7.0;
    // cyl->radius = 1.5;
    // cyl->color = 0xffff00;
    // new5 = new_object(cyl, 0);
    // add_object(&specs->obj_list, new5);
    

    printf("BEFORE OBJ LOOP\n");

    printf(" \n CAMERA \n camera position x = %f, y = %f, z = %f \n camera direction x = %f, y = %f, z = %f\n",
	specs->camera.x, specs->camera.y,  specs->camera.z, specs->view_dir.x, specs->view_dir.y, specs->view_dir.z);
    objects = specs->obj_list;
    
    // while(objects)
    // {
    //     if (objects->id == 1)
    //     {
    //     printf(" \n SPHERE \n center x = %f y = %f z = %f, radius = %f, color = %d\n", ((t_sphere *)objects->obj)->center.x, ((t_sphere *)objects->obj)->center.y, ((t_sphere *)objects->obj)->center.z, ((t_sphere *)objects->obj)->radius, ((t_sphere *)objects->obj)->color);
    //     }
    //     objects = objects->next;
    // }

    printf("AFTER OBJ LOOP\n");


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

double	ft_abs(double x)
{
	return ((x < 0) ? -x : x);
}

double		ft_max(double a, double b)
{
	return ((a > b) ? a : b);
}

int     distant_light(t_ray *ray, t_rt *specs, t_ray *shadow_ray, t_obj *lights)
{
    t_light     *light;

    light = (t_light *)lights->obj;
    shadow_ray->direct = light->direct;
    shadow_ray->t = FAR;
    intersect_object(shadow_ray, specs);
    if (shadow_ray->t == FAR)
    {
        ray->illum += ft_max(vec3_dot_product(ray->hitnormal, shadow_ray->direct), 0) * light->intensity;
        if (ray->illum > 1)
			ray->illum = 1;
    }
    return (0);

}
/*
int		lighting_spherical(t_ray *ray, t_rt *specs, t_ray *shadow_ray, t_obj *l)
{
	t_light	*light;
	double		dist;

	light = (t_light *)l->obj;
	shadow_ray->direct = vec3_combine_vec(&light->center, &ray->hitpoint, '-');
	shadow_ray->t = sqrt(vec3_dot_product(shadow_ray->direct, shadow_ray->direct));
	shadow_ray->direct = norm(shadow_ray->direct);
	dist = shadow_ray->t;
	intersect_object(shadow_ray, specs);
	if (shadow_ray->t == dist)
	{
		ray->illum += ft_max(vec3_dot_product(ray->hitnormal, shadow_ray->direct), 0) * light->intensity / (dist * dist); //technically 4 * M_PI * radius^2 but since intensity is arbitrary doesnt matter for now assuming white light
		if (ray->illum > 1)
			ray->illum = 1;
	}
	return (0);
}
*/
int     lighting(t_ray *ray, t_rt *specs)
{
    t_ray   shadow_ray;
    t_obj   *lights;

    lights = specs->light_list;
    intersection_vec3(ray);
    ray->illum = 0.1;
    shadow_ray.origin = ray->hitpoint;
    // while(lights)
    // {
        distant_light(ray, specs, &shadow_ray, lights);
    //     lights = lights->next;
    // }

    return (1);

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
    //ray.direct = norm(ray.direct);
    ray.t = FAR;
    ray.near_col = 0x88;
    intersect_object(&ray, specs);
    if (ray.t < FAR)
    {
        lighting(&ray, specs);
        v.red = ((ray.near_col >> 16) & 0xff) * ray.illum;
        v.green = ((ray.near_col >> 8) & 0xff) * ray.illum;
        v.blue = (ray.near_col & 0xff) * ray.illum;
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

void	usage(void)
{
	ft_putendl("file error");
}
//ft_strncmp(line, "plateau", 6) == 0


int get_camera_data(char **file, int *curr_line)
{
	// int *i;
	// int *j; 

	if (check_next_char(file, curr_line, "{") == -1)
		return (-1);
	if (find_vec(file, curr_line, "origin", 0) == -1)
		return (-1);
	get_vector_value(file[*curr_line]);
	if (find_vec(file, curr_line, "direction", 0) == -1)
		return (-1);
	get_vector_value(file[*curr_line]);
	if (check_next_char(file, curr_line, "}") == -1)
		return (-1);
	return (1);
}

int parse_camera(char **file, int *curr_line)
{
	int i; 

	i = -1;

	while (file[++(*curr_line)])
	{
		while (*file[*curr_line] == '#')
			++(*curr_line);
		if (ft_strncmp(file[*curr_line], "camera", 6) == 0)
			break ;
		else if ((ft_strncmp(file[*curr_line], "light", 5) == 0) ||
					(ft_strncmp(file[*curr_line], "objects", 7) == 0) ||
					file[*curr_line + 1] == NULL)
			return (-1);
	}
	if (get_camera_data(file, curr_line) == - 1)
		return (-1);
	return (1);
}
// #sphere
// light
// {
// 	origin(3000, 0, 5000)
// 	color(ffff00)
// 	radius(0.5)
// 	intensity(1)
// }

int get_light_data(char **file, int *curr_line)
{
	// int *i;
	// int *j;

	if (check_next_char(file, curr_line, "{") == -1)
		return (-1);
	if (find_vec(file, curr_line, "origin", 0) == -1)
		return (-1);
	//printf("%s\n", file[*curr_line]);
	get_vector_value(file[*curr_line]);
	if (find_color(file, curr_line, "color") == -1)
		return (-1);
	get_color_value(file[*curr_line]);

	if (find_vec(file, curr_line, "radius", 1) == -1)
		return (-1);
	
	//give double radius
	get_single_value(file[*curr_line]);
	if (find_vec(file, curr_line, "intensity", 1) == -1)
		return (-1);
	//give double intensity
	get_single_value(file[*curr_line]);
	if (check_next_char(file, curr_line, "}") == -1)
		return (-1);
	return (1);
}

int parse_light(char **file, int *curr_line)
{
	int i; 

	i = -1;

	while (file[++(*curr_line)])
	{
		while (*file[*curr_line] == '#')
			++(*curr_line);
		if (ft_strncmp(file[*curr_line], "light", 5) == 0)
			break ;
		else if ((ft_strncmp(file[*curr_line], "objects", 7) == 0) ||
					file[*curr_line + 1] == NULL)
			return (-1);
	}
	if (get_light_data(file, curr_line) == - 1)
		return (-1);
	return (1);
}
// #sphere
// light
// {
// 	origin(3000, 0, 5000)
// 	color(ffff00)
// 	radius(0.5)
// 	intensity(1)
// }

// objects
// {
// 	object(sphere)
// 	{
// 		origin(5, 0, 0)
// 		color(ff00ff)
// 		radius(2)
// 		...
// 	}

int parse_sphere(char **file, int *curr_line)
{
	printf("ok sphere\n");
	if (check_next_char(file, curr_line, "{") == -1)
		return (-1);
	if (find_vec(file, curr_line, "origin", 0) == -1)
		return (-1);
	//printf("%s\n", file[*curr_line]);
	get_vector_value(file[*curr_line]);
	if (find_color(file, curr_line, "color") == -1)
		return (-1);
	get_color_value(file[*curr_line]);

	if (find_vec(file, curr_line, "radius", 1) == -1)
		return (-1);
	
	//give double radius
	get_single_value(file[*curr_line]);
	if (check_next_char(file, curr_line, "}") == -1)
		return (-1);
	// file = 0;
	// printf("sphere BEFORE %d\n", *curr_line);
	// *curr_line += 6;
	// printf("sphere AFTER %d\n", *curr_line);
	return (1);
}

int parse_cylinder(char **file, int *curr_line)
{
	printf("ok cylinder\n");
	if (check_next_char(file, curr_line, "{") == -1)
		return (-1);
	if (find_vec(file, curr_line, "origin", 0) == -1)
		return (-1);
	//printf("%s\n", file[*curr_line]);
	//origin
	get_vector_value(file[*curr_line]);

	if (find_vec(file, curr_line, "axis", 0) == -1)
		return (-1);
	//axis
	get_vector_value(file[*curr_line]);

	if (find_vec(file, curr_line, "max", 1) == -1)
		return (-1);
	//give double max
	get_single_value(file[*curr_line]);

	if (find_vec(file, curr_line, "radius", 1) == -1)
		return (-1);
	//give double radius
	get_single_value(file[*curr_line]);


	if (find_color(file, curr_line, "color") == -1)
		return (-1);
	get_color_value(file[*curr_line]);

	if (check_next_char(file, curr_line, "}") == -1)
		return (-1);
	// file = 0;
	// printf("plane BEFORE%d\n", *curr_line);
	// *curr_line += 5;
	// printf("plane AFTER%d\n", *curr_line);
	return (1);
}

int parse_cone(char **file, int *curr_line)
{
	printf("ok cone\n");
	if (check_next_char(file, curr_line, "{") == -1)
		return (-1);
	if (find_vec(file, curr_line, "center", 0) == -1)
		return (-1);
	//printf("%s\n", file[*curr_line]);
	//origin
	get_vector_value(file[*curr_line]);

	if (find_vec(file, curr_line, "axis", 0) == -1)
		return (-1);
	//axis
	get_vector_value(file[*curr_line]);

	if (find_vec(file, curr_line, "height", 1) == -1)
		return (-1);
	//give double max
	get_single_value(file[*curr_line]);

	if (find_vec(file, curr_line, "max", 1) == -1)
		return (-1);
	//give double max
	get_single_value(file[*curr_line]);

	if (find_vec(file, curr_line, "min", 1) == -1)
		return (-1);
	//give double radius
	get_single_value(file[*curr_line]);

	if (find_vec(file, curr_line, "angle", 1) == -1)
		return (-1);
	//give double max
	get_single_value(file[*curr_line]);


	if (find_color(file, curr_line, "color") == -1)
		return (-1);
	get_color_value(file[*curr_line]);

	if (check_next_char(file, curr_line, "}") == -1)
		return (-1);
	// file = 0;
	// printf("cone BEFORE%d\n", *curr_line);
	// *curr_line += 9;
	// printf("cone AFTER%d\n", *curr_line);
	return (1);
}

int parse_plane(char **file, int *curr_line)
{
	
	if (check_next_char(file, curr_line, "{") == -1)
		return (-1);
	if (find_vec(file, curr_line, "point", 0) == -1)
		return (-1);
	//printf("%s\n", file[*curr_line]);
	get_vector_value(file[*curr_line]);
	printf("ok plane\n");

	if (find_vec(file, curr_line, "normal", 0) == -1)
		return (-1);
	//give double radius
	get_vector_value(file[*curr_line]);

	if (find_color(file, curr_line, "color") == -1)
		return (-1);
	get_color_value(file[*curr_line]);

	if (check_next_char(file, curr_line, "}") == -1)
		return (-1);

	// file = 0;
	// printf("cylinder BEFORE%d\n", *curr_line);
	// *curr_line += 7;
	// printf("cylinder AFTER%d\n", *curr_line);
	return (1);
}


int get_obj_type(char **file, int *curr_line)
{
	//printf("check\n");
	while(*file[*curr_line] == '\t' || *file[*curr_line] == ' ')
			file[*curr_line] += 1;
	if (ft_strncmp(file[*curr_line], "object(sphere)", 14) == 0)
	{
		if (parse_sphere(file, curr_line) == -1)
		{
			printf("SPHERE FAIL\n");
			return (-1);
		}
	}
	else if (ft_strncmp(file[*curr_line], "object(plane)", 13) == 0)
	{
		if (parse_plane(file, curr_line) == -1)
		{
			printf("PLANE FAIL\n");
			return (-1);
		}
	}
	else if (ft_strncmp(file[*curr_line], "object(cone)", 12) == 0)
	{
		if (parse_cone(file, curr_line) == -1)
		{
			printf("CONE FAIL\n");
			return (-1);
		}	
	}
	else if (ft_strncmp(file[*curr_line], "object(cylinder)", 16) == 0)
	{
		if (parse_cylinder(file, curr_line) == -1)
		{
			printf("CYLINDRE FAIL\n");
			return (-1);
		}
	}
	else
	{
		if(*file[*curr_line] == '\t')
			printf("hahaha\n");
		printf("%s\n", file[*curr_line]);
		return (-1);
	}	
	return (1);
}

int get_obj_data(char **file, int *curr_line)
{
	// int *i;
	// int *j;

	if (check_next_char(file, curr_line, "{") == -1)
		return (-1);
	while (file[++(*curr_line)])
	{
		printf(" iterations\n");
		if (get_obj_type(file, curr_line) == -1)
		{
			printf("no more objects left\n");
			break ;
		}	
			
	}
	return (1);
}


int parse_obj(char **file, int *curr_line)
{
	int i; 

	i = -1;

	while (file[++(*curr_line)])
	{
		while (*file[*curr_line] == '#')
			++(*curr_line);
		if (ft_strncmp(file[*curr_line], "objects", 5) == 0)
			break ;
		else if (file[*curr_line + 1] == NULL)
			return (-1);
	}
	if (get_obj_data(file, curr_line) == - 1)
		return (-1);
	return (1);
}

int parse_data(char	**file)
{
	int i;

	i = -1;
	//ft_print_tab2(file);
	//skip comments
	// while (file[++i][0] == '#')
	// 	;
	///1. look for camera
	if (parse_camera(file, &i) == -1)
		return (-1);
	if (parse_light(file, &i) == -1)
		return (-1);
	parse_obj(file, &i);
	//printf("ret = %d\n", ret);
	///2. look for light (optionnel)

	///3. look for object

	return (1);
}
/**
* ALMOST DONE
*/
int			main(int argc, char **argv)
{
//	t_rt		specs;
	int			fd;
	char **file;

	argc = 1;
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (0);
	
	file = ft_file_read(fd);
	if (file == NULL)
	{
		usage();
		return (0);
	}	
	//ft_print_tab2(file);
	//init_rt_struct(&specs);
	if (parse_data(file) == -1)
	{
		printf("file error\n");
		return (0);
	}	
		
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
    
    //parsing();
    //specs.view_dir = norm(specs.view_dir);
    //printf("BEFORE DRAW\n");
   // draw_image(&specs);
    //printf("AFTER DRAW\n");
	//mlx_key_hook(specs.win, deal_key, &specs);
	//mlx_loop(specs.mlx);
	return (0);
}