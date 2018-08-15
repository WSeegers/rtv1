/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:12:39 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/15 16:30:29 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_scene.h"

int		parse_splitcount(char **split)
{
	int i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

void	parse_error(char *line)
{
	f_printf("Invalid config: %s\n", line);
	f_exit(0);
}

t_vec3	parse_vector(char *s_vector)
{
	t_vec3	ret;
	char	**split;

	split = f_strsplit(s_vector, ',');
	if (parse_splitcount(split) != 3)
		parse_error(s_vector);
	ret.x = f_atof(split[0]);
	ret.y = f_atof(split[1]);
	ret.z = f_atof(split[2]);
	f_strarrdel(split);
	return (ret);
}

t_colour	parse_colour(char *s_colour)
{
	t_colour	ret;
	char		**split;

	split = f_strsplit(s_colour, ',');
	if (parse_splitcount(split) != 3)
		parse_error(s_colour);
	ret = colour_get(f_atof(split[0]), f_atof(split[1]), f_atof(split[2]));
	f_strarrdel(split);
	return (ret);
}

void	parse_camera(t_camera *cam, char *s_camera)
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

	fconfig = f_openf("./scene-config", 'r');
	while (f_next_line(&line, fconfig))
	{
		if (line[1] == '|')
		{
			if (line[0] == 'c')
				parse_camera(&scene->camera, line);
			else if (line[0] == 's')
				add_shape(scene->shapes, parse_shape(line));
			else if (line[0] == 'a')
				scene->ambience = parse_ambiance(line);
			else if (line[0] == 'l')
				add_light(scene->lights, parse_light(line));
		}
		else if (!(line[0] == '#') && (strlen(line)))
			parse_error(line);
		f_printf("%s\n", line);
		f_strdel(&line);
	}
	if (!(scene->camera.forward.x + scene->camera.forward.y +
			scene->camera.forward.z))
		parse_error("No appropriate camera was set");

	//Debugging
	f_printf("light total: %u\n", scene->lights->total);
	f_printf("shapes total: %u\n", scene->shapes->total);
	f_closef(fconfig);
	f_printf("end\n");
}
