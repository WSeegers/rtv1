/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 22:26:28 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/08 17:10:05 by wseegers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "gen_scene.h"

static bool	init(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		f_printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return (false);
	}
	else
	{
		if (!(g_window = SDL_CreateWindow(SCREEN_TITLE, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN)))
		{
			f_printf("Window could not be created! SDL_Error: %s\n",
				SDL_GetError());
			return (false);
		}
		g_wsurface = SDL_GetWindowSurface(g_window);
	}
	return (true);
}

static void	end(void)
{
	SDL_DestroyWindow(g_window);
	SDL_Quit();
}

static void	loop(void)
{
	SDL_Event	e;
	bool		quit;

	quit = false;
	while (!quit)
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = true;
			else if (e.type == SDL_KEYDOWN &&
				e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				quit = true;
		}
}

int			main(void)
{
	t_scene				scene;

	if (!init())
		SDL_Quit();
	scene.shapes = vshape_set_create();
	scene.lights = vlight_set_create();
	f_printf("Init scene\n");
	gen_scene4(&scene);
	f_printf("Generating view, please wait...\n");
	generate_screen(scene.camera, scene.shapes, scene.lights);
	f_printf("Blit\n");
	SDL_UpdateWindowSurface(g_window);
	loop();
	end();
}
