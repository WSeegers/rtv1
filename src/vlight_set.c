/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vlight_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 10:32:22 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/04 10:32:31 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_vlight_set	vlight_set_create(void)
{
	return (vector_create());
}

void	add_light(t_vlight_set scene, t_light *light)
{
	vector_add(scene, light);
}

t_light *get_light(t_vlight_set scene, int index)
{
	return ((t_light*)vector_get(scene, index));
}
