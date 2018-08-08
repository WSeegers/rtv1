/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_scene3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:09:45 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/08 17:10:22 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_scene.h"
#include "colour.h"

static void	add_shapes(t_vshape_set shapes)
{
	t_sphere	*sphere;
	t_cylinder	*cyl;
	t_vec3		orig;
	int			i;

	cyl = create_cylinder(VEC3(0, 0, 0), VEC3(0, 1, 0), 1, C_OLIVE);
	add_shape(shapes, (t_shape*)cyl);
	i = -1;
	while (i++ < 14)
	{
		orig = VEC3(cos(i) * 3, i * 3 - 10, sin(i) * 2);
		sphere = create_sphere(orig, 1, C_WHITE);
		add_shape(shapes, (t_shape*)sphere);
	}
}

static void	add_walls(t_vshape_set shapes)
{
	t_plane		*back_wall;
	t_plane		*pfloor;

	back_wall = plane_create(VEC3(0, 0, 40), VEC3(0, 0, -1), C_GREEN);
	add_shape(shapes, (t_shape*)back_wall);
	pfloor = plane_create(VEC3(0, -20, -40), VEC3(0, 1, 0), C_BLUE);
	add_shape(shapes, (t_shape*)pfloor);
}

static void	add_lights(t_vlight_set lights)
{
	t_light	*light;

	light = light_create(VEC3(45, 15, -30), C_WHITE, 0.5);
	add_light(lights, light);
	light = light_create(VEC3(10, 15, -30), C_WHITE, 0.3);
	add_light(lights, light);
}

void		gen_scene3(t_scene *scene)
{
	camera_set(VEC3(15, 20, -30), VEC3(0, 10, 0), &scene->camera);
	add_walls(scene->shapes);
	add_lights(scene->lights);
	add_shapes(scene->shapes);
}
