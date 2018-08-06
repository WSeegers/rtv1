/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 23:56:25 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/06 22:42:18 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "f_math.h"

t_colour	get_specular(t_intersect s_intersect, t_intersect l_intersect, t_light light)
{
	t_vec3		half_dir;
	double		angle;
	t_colour	ret;

	half_dir = vec3_normalize(vec3_subtract(vec3_negate(s_intersect.ray.d), l_intersect.ray.d));
	angle = MAX(vec3_dot(half_dir, s_intersect.normal), 0.0);
	ret = colour_scale(C_WHITE, pow(angle, 64 * 8));
	return (ret);
}

t_colour	get_diffuse(t_intersect s_intersect, t_intersect l_intersect, t_light light)
{
	double		angle;
	t_colour	ret;

	angle = MAX(-vec3_dot(l_intersect.ray.d, s_intersect.normal), 0);
	ret = colour_scale(light.colour, angle);
	ret = colour_multiply(s_intersect.shape->colour, ret);
	return (ret);
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
			ret = colour_add(ret, get_diffuse(s_intersect, l_intersect, light));
			ret = colour_add(ret, get_specular(s_intersect, l_intersect, light));
			// if (-vec3_dot(dir, s_intersect.normal) > 0)
			// {
			// 	double dot = vec3_dot(vec3_reflect(l_intersect.ray.d, l_intersect.normal), vec3_negate(s_intersect.ray.d));
			// 	dot = pow(dot, 16);
			// 	if (dot > 0)
			// 	{
			// 		temp = colour_scale(light.colour, dot);
			// 		ret = colour_add(ret, temp);
			// 	}
			// }
		}
	}
	

	return (ret);
}

static void	set_ray(int x, int y, t_ray *ray, t_camera cam)
{
	double	rx;
	double	ry;
	t_vec3	fwd;
	t_vec3	right;
	t_vec3	up;

	fwd = cam.forward;
	rx = (-1.0 + (((double)x / SCREEN_WIDTH) * 2.0)) * FOV;
	ry = -(-1.0 + (((double)y / SCREEN_HEIGHT) * 2.0)) * ASPECT_RATIO * FOV;
	right = vec3_scale(rx, cam.right);
	up = vec3_scale(ry, cam.up);
	ray->d = vec3_normalize(vec3_add(vec3_add(fwd, up), right));
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