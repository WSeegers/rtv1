/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_scene1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 14:00:54 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/08 17:08:15 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_scene.h"
#include "colour.h"

static void	add_shapes(t_vshape_set shapes)
{
	t_sphere	*s;
	t_cylinder	*c;

	s = create_sphere(VEC3(0, 8, 15), 8, C_AZURE);
	add_shape(shapes, (t_shape*)s);
	s = create_sphere(VEC3(-15, 0, 0), 5, C_SILVER);
	add_shape(shapes, (t_shape*)s);
	s = create_sphere(VEC3(15, 0, 0), 5, C_SILVER);
	add_shape(shapes, (t_shape*)s);
	s = create_sphere(VEC3(-15, 0, 30), 5, C_SILVER);
	add_shape(shapes, (t_shape*)s);
	s = create_sphere(VEC3(15, 0, 30), 5, C_SILVER);
	add_shape(shapes, (t_shape*)s);
	c = create_cylinder(VEC3(-15, 0, 0), VEC3(0, 1, 0), 2.5, C_SILVER);
	add_shape(shapes, (t_shape*)c);
	c = create_cylinder(VEC3(15, 0, 0), VEC3(0, 1, 0), 2.5, C_SILVER);
	add_shape(shapes, (t_shape*)c);
	c = create_cylinder(VEC3(15, 0, 30), VEC3(0, 1, 0), 2.5, C_SILVER);
	add_shape(shapes, (t_shape*)c);
	c = create_cylinder(VEC3(-15, 0, 30), VEC3(0, 1, 0), 2.5, C_SILVER);
	add_shape(shapes, (t_shape*)c);
}

static void	add_walls(t_vshape_set shapes)
{
	t_plane		*left_wall;
	t_plane		*back_wall;
	t_plane		*right_wall;
	t_plane		*pfloor;

	left_wall = plane_create(VEC3(-40, 0, 0), VEC3(1, 0, 0), C_BURGANDY);
	add_shape(shapes, (t_shape*)left_wall);
	right_wall = plane_create(VEC3(40, 0, 0), VEC3(-1, 0, 0), C_GREEN);
	add_shape(shapes, (t_shape*)right_wall);
	back_wall = plane_create(VEC3(0, 0, 80), VEC3(0, 0, -1), C_BLUE);
	add_shape(shapes, (t_shape*)back_wall);
	pfloor = plane_create(VEC3(0, 0, -10), VEC3(0, 1, 0), C_OLIVE);
	add_shape(shapes, (t_shape*)pfloor);
}

static void	add_lights(t_vlight_set lights)
{
	t_light	*light;

	light = light_create(VEC3(0, 100, 30), C_WHITE, 0.3);
	add_light(lights, light);
	light = light_create(VEC3(0, 15, -30), C_WHITE, 0.5);
	add_light(lights, light);
}

void		gen_scene1(t_scene *scene)
{
	camera_set(VEC3(10, 15, -30), VEC3(0, 10, 0), &scene->camera);
	add_walls(scene->shapes);
	add_lights(scene->lights);
	add_shapes(scene->shapes);
}
