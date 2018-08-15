/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 15:25:17 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/15 15:46:11 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	scene_init(t_scene *scene)
{
	scene->ambience = COLOUR(0, 0, 0);
	scene->camera.forward = VEC3(0, 0, 0);
	scene->shapes = vshape_set_create();
	scene->lights = vlight_set_create();
}
