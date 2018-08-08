/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putpixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 23:29:46 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/08 13:27:24 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		putpixel(int x, int y, t_colour pixel)
{
	putipixel(x, y, colour_to_int(pixel));
}

static void	check_endianess(Uint8 *p, Uint32 pixel)
{
	if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
	{
		p[0] = (pixel >> 16) & 0xff;
		p[1] = (pixel >> 8) & 0xff;
		p[2] = pixel & 0xff;
	}
	else
	{
		p[0] = pixel & 0xff;
		p[1] = (pixel >> 8) & 0xff;
		p[2] = (pixel >> 16) & 0xff;
	}
}

void		putipixel(int x, int y, Uint32 pixel)
{
	int		bpp;
	Uint8	*p;

	bpp = g_wsurface->format->BytesPerPixel;
	p = (Uint8 *)g_wsurface->pixels + y * g_wsurface->pitch + x * bpp;
	if (bpp == 1)
		*p = pixel;
	else if (bpp == 2)
		*(Uint16 *)p = pixel;
	else if (bpp == 3)
	{
		check_endianess(p, pixel);
	}
	else if (bpp == 4)
		*(Uint32 *)p = pixel;
}
