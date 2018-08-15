/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:16:11 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/15 15:53:33 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_SCENE_H
# define PARSE_SCENE_H

# include "scene.h"
# include "f_string.h"
# include "f_cntl.h"

# define P_PLANE	"P"
# define P_SPHERE	"S"
# define P_CYLINDER	"Cy"
# define P_CONE		"Co"

typedef struct s_scene	t_scene;

void					parse_scene(t_scene *scene);
t_shape					*parse_shape(char *s_shape);

#endif