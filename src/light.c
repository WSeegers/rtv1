/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 16:32:29 by wseegers          #+#    #+#             */
/*   Updated: 2018/07/31 20:05:48 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "f_memory.h"

t_light			*light_create(t_vec3 origin, t_colour colour)
{
	t_light *ret;

	ret = (t_light*)f_memalloc(sizeof(t_light));
	ret->origin = origin;
	ret->colour = colour;
	return (ret);
}

void			init_light(t_light *light, t_vec3 origin, t_colour colour)
{
	light->origin = origin;
	light->colour = colour;
}
