/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers.mauws@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 13:58:56 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/05 21:25:12 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colour.h"

t_colour	colour_get(double red, double green, double blue)
{	
	red = CLAMP(red, 0.0, 1.0);
	green = CLAMP(green, 0.0, 1.0);
	blue = CLAMP(blue, 0.0, 1.0);
	return ((t_colour){red, green, blue});
}

t_icolour	colour_to_int(t_colour col)
{
	t_icolour icol;
	unsigned char red;
	unsigned char green;
	unsigned char blue;

	red = col.r * 255;
	green = col.g * 255;
	blue = col.b * 255;
	icol = 0 | blue | (green << 8) | (red << 16);
	return (icol);
}

t_colour	colour_add(t_colour c1, t_colour c2)
{
	c1.r += c2.r;
	c1.g += c2.g;
	c1.b += c2.b;
	c1.r = CLAMP(c1.r, 0.0, 1.0);
	c1.g = CLAMP(c1.g, 0.0, 1.0);
	c1.b = CLAMP(c1.b, 0.0, 1.0);
	return (c1);
}

t_colour	colour_multiply(t_colour c1, t_colour c2)
{
	c1.r *= c2.r;
	c1.g *= c2.g;
	c1.b *= c2.b;
	return (c1);
}

t_colour	colour_scale(t_colour c, double s)
{
	s = CLAMP(s, 0.0, 1.0);
	c.r *= s;
	c.g *= s;
	c.b *= s;
	return (c);
}