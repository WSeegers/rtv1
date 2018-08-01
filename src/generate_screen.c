/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 23:56:25 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/31 20:05:56 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "f_math.h"

bool	cast_ray(t_ray ray, t_vshape_set shapes, t_intersect *intercect)
{
	int i;
	t_shape *shape;
	t_intersect temp;
	t_colour col;

	i = -1;
	col = C_BLACK;
	while (++i < shapes->total)
	{
		shape = get_shape(shapes, i);
		if (shape->intersect(shape, ray, &temp))
		{
			if (temp.t < ray.t_max)
			{
				intercect->shape = shape;
				ray.t_max = temp.t;
				*intercect = temp;
			}
		}
	}
	return (ray.t_max != RAY_T_MAX);
}

void	set_ray(int x, int y, t_ray *ray, t_camera cam)
{
	double	rx;
	double	ry;
	t_vec3	fwd;
	t_vec3	right;
	t_vec3	up;

	fwd = cam.forward;
	rx = (-1.0 + (((double)x / SCREEN_WIDTH) * 2.0)) * FOV;
	ry = -(-1.0 + (((double)y / SCREEN_HEIGHT) * 2.0)) * ASPECT_RATIO * FOV;
	ray->t_max = RAY_T_MAX;
	right = vec3_scale(rx, cam.right);
	up = vec3_scale(ry, cam.up);
	ray->d = vec3_normalize(vec3_add(vec3_add(fwd, up), right));
}

t_colour	eval_light(t_intersect s_intersect, t_vshape_set shapes, t_vlight_set lights)
{
	t_intersect	l_intersect;
	t_colour ret;
	t_colour temp;

	ret = s_intersect.shape->colour;
	ret = colour_multiply(ret, AMBIENT_LIGHT);

	t_vec3 dir;
	t_light light;
	int i;

	i = -1;
	while (++i < lights->total)
	{
		light = *(get_light(lights, i));
		t_vec3 dir = vec3_normalize(vec3_subtract(ray_calculate(s_intersect.ray, s_intersect.t), light.origin));
		cast_ray(RAY(light.origin, dir), shapes, &l_intersect);
		if(l_intersect.shape == s_intersect.shape)
		{
			temp = colour_scale(light.colour, -vec3_dot(dir, s_intersect.normal));
			temp = colour_multiply(s_intersect.shape->colour, temp);
			ret = colour_add(ret, temp);
		}
	}
	

	return (ret);
}

void	generate_screen(t_camera cam, t_vshape_set shapes, t_vlight_set lights)
{
	int		x;
	int		y;
	t_ray	ray;
	t_intersect intersect;
	t_colour col;

	ray.p = cam.origin;
	y = -1;
	while (++y < SCREEN_HEIGHT && (x = -1))
	{
		while (++x < SCREEN_WIDTH)
		{
			set_ray(x, y, &ray, cam);
			col = C_BLACK;
			if (cast_ray(ray, shapes, &intersect))
				 col = eval_light(intersect, shapes, lights);
			putpixel(x, y, col);
		}
	}
}