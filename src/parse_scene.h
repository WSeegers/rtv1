/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:16:11 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/20 03:36:31 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_SCENE_H
# define PARSE_SCENE_H

# include "f_string.h"
# include "f_cntl.h"
# include "scene.h"

# define P_PLANE	"P"
# define P_SPHERE	"S"
# define P_CYLINDER	"Cy"
# define P_CONE		"Co"

typedef struct s_scene	t_scene;

void					parse_scene(t_scene *scene);
t_shape					*parse_shape(char *s_shape);
void					parse_camera(t_camera *cam, char *s_camera);
t_colour				parse_ambiance(char *s_alight);
t_light					*parse_light(char *s_light);
int						parse_splitcount(char **split);
void					parse_error(char *line);
t_vec3					parse_vector(char *s_vector);
t_colour				parse_colour(char *s_colour);

#endif
