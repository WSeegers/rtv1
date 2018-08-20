/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 03:32:08 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/20 03:36:14 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_scene.h"

int			parse_splitcount(char **split)
{
	int i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

void		parse_error(char *line)
{
	f_printf("Invalid config: %s\n", line);
	f_exit(0);
}

t_vec3		parse_vector(char *s_vector)
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
