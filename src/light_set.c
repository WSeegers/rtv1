/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 19:10:33 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/31 19:13:50 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
