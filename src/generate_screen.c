/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 23:56:25 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/20 03:42:52 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "f_math.h"

static void	set_ray(int x, int y, t_ray *ray, t_camera cam)
{
	double	rx;
	double	ry;
	t_vec3	fwd;
	t_vec3	right;
	t_vec3	up;

	fwd = cam.forward;
	rx = (-1.0 + (((double)x / SCREEN_WIDTH) * 2.0)) * FOV;
	ry = -(-1.0 + (((double)y / SCREEN_HEIGHT) * 2.0)) * FOV * ASPECT_RATIO;
	right = vec3_scale(rx, cam.right);
	up = vec3_scale(ry, cam.up);
	ray->d = vec3_normalize(vec3_add(vec3_add(fwd, up), right));
}

void		generate_screen(t_scene *scene)
{
	int			x;
	int			y;
	t_ray		ray;
	t_intersect intersect;
	t_colour	col;

	ray.p = scene->camera.origin;
	y = -1;
	while (++y < SCREEN_HEIGHT && (x = -1))
	{
		while (++x < SCREEN_WIDTH)
		{
			set_ray(x, y, &ray, scene->camera);
			col = C_BLACK;
			if (cast_ray(ray, scene->shapes, &intersect))
				col = eval_light(intersect, scene);
			putpixel(x, y, col);
		}
	}
}
