/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_scene4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:33:10 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/15 09:46:42 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_scene.h"
#include "colour.h"
#include <stdlib.h>
#include <time.h>

static t_vec3	vec3_rand(double min, double max)
{
	double	dist;
	t_vec3	ret;

	dist = (max - min);
	ret.x = rand() * dist / RAND_MAX - dist / 2;
	ret.y = rand() * dist / RAND_MAX - dist / 2;
	ret.z = rand() * dist / RAND_MAX - dist / 2;
	return (ret);
}

static t_colour	randcol(void)
{
	t_colour	col;

	col.r = rand() / (double)RAND_MAX;
	col.g = rand() / (double)RAND_MAX;
	col.b = rand() / (double)RAND_MAX;
	return (col);
}

static void		add_shapes(t_vshape_set shapes)
{
	t_sphere	*sphere;
	t_cylinder	*cyl;
	t_vec3		orig;
	int			i;

	cyl = create_cylinder(VEC3(0, 0, 0), VEC3(0, 1, 0), 1, C_OLIVE);
	add_shape(shapes, (t_shape*)cyl);
	i = -1;
	while (i++ < 20)
	{
		orig = vec3_rand(-40, 40);
		sphere = create_sphere(orig, rand() * 5.0 / RAND_MAX + 1, randcol());
		add_shape(shapes, (t_shape*)sphere);
	}
}

static void		add_lights(t_vlight_set lights)
{
	t_light	*light;

	light = light_create(VEC3(45, 15, -30), C_WHITE, 0.5);
	add_light(lights, light);
	light = light_create(VEC3(10, 15, -30), C_WHITE, 0.3);
	add_light(lights, light);
}

void			gen_scene4(t_scene *scene)
{
	srand(time(NULL));
	camera_set(VEC3(15, 20, -50), VEC3(0, 10, 0), &scene->camera);
	add_lights(scene->lights);
	add_shapes(scene->shapes);
	add_shape(scene->shapes, (t_shape*)plane_create(VEC3(0, 0, 40),
		VEC3(0, 0, -1), C_GREEN));
}
