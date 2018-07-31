/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 23:56:25 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/31 16:08:32 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "f_math.h"

bool	cast_ray(t_ray ray, t_vshape_set scene, t_intersect *intercect)
{
	int i;
	t_shape *shape;
	t_intersect temp;
	t_colour col;

	i = -1;
	col = C_BLACK;
	while (++i < scene->total)
	{
		shape = get_shape(scene, i);
		if (shape->intersect(shape, ray, &temp))
		{
			if (temp.t < ray.t_max)
			{
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
	rx = (-1.0 + (((double)x / SCREEN_WIDTH) * 2.0));
	ry = -(-1.0 + (((double)y / SCREEN_HEIGHT) * 2.0)) * ASPECT_RATIO;
	ray->t_max = RAY_T_MAX;
	right = vec3_scale(rx, cam.right);
	up = vec3_scale(ry, cam.up);
	ray->d = vec3_normalize(vec3_add(vec3_add(fwd, up), right));
}

void	generate_screen(t_camera cam, t_vshape_set scene)
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
			if (cast_ray(ray, scene, &intersect))
			{
				// test
				col = intersect.shape->colour;
				col = colour_multiply(col, AMBIENT_LIGHT);
				
			}
			putpixel(x, y, col);
		}
	}
}