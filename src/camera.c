/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 15:26:00 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/08 19:35:45 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	camera_set(t_vec3 origin, t_vec3 target, t_camera *cam)
{
	cam->origin = origin;
	cam->forward = vec3_normalize(vec3_subtract(target, origin));
	cam->right = vec3_cross(UP_GUIDE, cam->forward);
	cam->up = vec3_cross(cam->forward, cam->right);
}

void	camera_set_target(t_vec3 target, t_camera *cam)
{
	cam->forward = vec3_normalize(vec3_subtract(target, cam->origin));
	cam->right = vec3_normalize(vec3_cross(cam->forward, UP_GUIDE));
	cam->up = vec3_normalize(vec3_cross(cam->forward, cam->right));
}
