/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:12:39 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/20 04:53:54 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_scene.h"

void		parse_camera(t_camera *cam, char *s_camera)
{
	char		**split;
	t_vec3		pos;
	t_vec3		look_at;

	split = f_strsplit(s_camera, '|');
	if (parse_splitcount(split) != 3)
		parse_error(s_camera);
	pos = parse_vector(split[1]);
	look_at = parse_vector(split[2]);
	camera_set(pos, look_at, cam);
	f_strarrdel(split);
}

t_shape		*parse_shape(char *s_shape)
{
	t_shape	*shape;
	char	**split;

	split = f_strsplit(s_shape, '|');
	if (parse_splitcount(split) != 6)
		parse_error(s_shape);
	shape = NULL;
	if (f_strstr(split[1], P_PLANE))
		shape = (t_shape*)plane_create(parse_vector(split[2]),
					parse_vector(split[3]), parse_colour(split[4]));
	else if (f_strstr(split[1], P_SPHERE))
		shape = (t_shape*)create_sphere(parse_vector(split[2]),
					f_atof(split[5]), parse_colour(split[4]));
	else if (f_strstr(split[1], P_CYLINDER))
		shape = (t_shape*)create_cylinder(parse_vector(split[2]),
					parse_vector(split[3]), f_atof(split[5]),
					parse_colour(split[4]));
	else if (f_strstr(split[1], P_CONE))
		shape = (t_shape*)create_cone(parse_vector(split[2]),
					parse_vector(split[3]), f_atof(split[5]),
					parse_colour(split[4]));
	else
		parse_error(s_shape);
	f_strarrdel(split);
	return (shape);
}

t_colour	parse_ambiance(char *s_alight)
{
	t_colour	ret;
	char		**split;

	split = f_strsplit(s_alight, '|');
	if (parse_splitcount(split) != 3)
		parse_error(s_alight);
	ret = parse_colour(split[1]);
	ret = colour_scale(ret, f_atof(split[2]));
	f_strarrdel(split);
	return (ret);
}

t_light		*parse_light(char *s_light)
{
	t_light *light;
	char	**split;

	split = f_strsplit(s_light, '|');
	if (parse_splitcount(split) != 4)
		parse_error(s_light);
	light = light_create(parse_vector(split[1]),
				parse_colour(split[2]), f_atof(split[3]));
	f_strarrdel(split);
	return (light);
}

void		parse_scene(t_scene *scene)
{
	t_file	*fconfig;
	char	*line;

	if (!(fconfig = f_openf("./scene-config", 'r')))
		parse_error("./scene-config was not found");
	while (f_next_line(&line, fconfig))
	{
		if (line[1] == '|' && line[0] == 'c')
			parse_camera(&scene->camera, line);
		else if (line[1] == '|' && line[0] == 's')
			add_shape(scene->shapes, parse_shape(line));
		else if (line[1] == '|' && line[0] == 'a')
			scene->ambience = parse_ambiance(line);
		else if (line[1] == '|' && line[0] == 'l')
			add_light(scene->lights, parse_light(line));
		else if (!(line[0] == '#') && (strlen(line)))
			parse_error(line);
		f_strdel(&line);
	}
	f_closef(fconfig);
	f_strdel(&line);
}
