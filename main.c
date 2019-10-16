int			init_rt_struct(int fd, t_rt *new)
{

}

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

/**
 * DONE
 */
void    intersect_object(t_ray *ray, t_rt *specs)
{
    t_obj   *o;

    o = specs->obj_list;
    while (o)
    {
        specs->ft_ptr[o->id](ray, o->obj);
        o = o->next;
    }

}

/**
 * .....
 */
int     trace_ray(float x, float y, t_rt *specs)
{
    raster_to_world(x, y, specs);
    intersect_object(&ray, specs);
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
void    loop_on_pixel(t_rt *specs)
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
            if(color = trace_ray((float)x / WIN_WIDTH, (float)y / WIN_HEIGHT) != -1)
                color_pixel(color, x, y, specs);
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
	specs->img = mlx_new_image(specs->mlx, W_IMG, H_IMG);
	specs->img_str = mlx_get_data_addr(specs->img, &specs->bpp,
	&specs->size_line, &specs->endian);
	loop_on_pixel(specs);
	mlx_put_image_to_window(specs->mlx, specs->win, specs->img, 0, 0);
	mlx_destroy_image(specs->mlx, specs->img);
}

/**
* ALMOST DONE
*/
int			main(int ac, char **av)
{
	t_rt		specs;
	int			fd;

	if (ac != 2)
	{
		ft_putstr("Usage: ./rtv1 scenefile\n");
		return (0);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		perror("");
		return (0);
	}
	//if (!init_rt_struct(fd, &specs))
	{
		ft_putstr_fd("Failed to read input file\n", 2);
		return (0);
	}

    //parsing();
    //specs.view_dir = normalise(specs.view_dir);
    draw_image(&specs);
	mlx_key_hook(specs.win, deal_key, &specs);
	mlx_loop(specs.mlx);
	return (0);
}