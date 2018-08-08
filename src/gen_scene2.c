/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_scene2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 14:49:33 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/08 17:08:23 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_scene.h"
#include "colour.h"

static void	add_shapes(t_vshape_set shapes)
{
	t_cylinder	*c;
	t_cone		*cone;
	t_sphere	*sphere;

	c = create_cylinder(VEC3(-15, 0, 0), VEC3(1, 1, 0), 2.5, C_RED);
	add_shape(shapes, (t_shape*)c);
	cone = create_cone(VEC3(15, 5, 0), VEC3(-1, 1, 0), 0.25, C_BLUE);
	add_shape(shapes, (t_shape*)cone);
	sphere = create_sphere(VEC3(0, 3, 0), 3, C_WHITE);
	add_shape(shapes, (t_shape*)sphere);
	sphere = create_sphere(VEC3(0, 2, -4), 1, C_WHITE);
	add_shape(shapes, (t_shape*)sphere);
	sphere = create_sphere(VEC3(6, 2, -2), 2, C_WHITE);
	add_shape(shapes, (t_shape*)sphere);
}

static void	add_walls(t_vshape_set shapes)
{
	t_plane		*back_wall;
	t_plane		*pfloor;

	back_wall = plane_create(VEC3(0, 0, 80), VEC3(0, 0, -1), C_GREEN);
	add_shape(shapes, (t_shape*)back_wall);
	pfloor = plane_create(VEC3(0, 0, -10), VEC3(0, 1, 0), C_OLIVE);
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

void		gen_scene2(t_scene *scene)
{
	camera_set(VEC3(15, 15, -30), VEC3(0, 10, 0), &scene->camera);
	add_walls(scene->shapes);
	add_lights(scene->lights);
	add_shapes(scene->shapes);
}
