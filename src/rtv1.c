/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wseegers <wseegers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 22:26:28 by wseegers          #+#    #+#             */
/*   Updated: 2018/08/15 09:41:01 by wseegers         ###   ########.fr       */
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

static void	select_scene(char selection, t_scene *scene)
{
	if (selection == '1')
		gen_scene1(scene);
	else if (selection == '2')
		gen_scene2(scene);
	else if (selection == '3')
		gen_scene3(scene);
	else
		gen_scene4(scene);
}

int			main(int ac, char *av[])
{
	t_scene	scene;
	char	*selection;		

	if (ac != 2 || f_strlen((selection = av[1])) != 1 || !f_strchr("1234", selection[0]))
	{
		f_printf("%s: usage: ./rtv1 [1-4]\n", av[0]);
		exit(0);
	}
	if (!init())
		SDL_Quit();
	scene.shapes = vshape_set_create();
	scene.lights = vlight_set_create();
	f_printf("Init scene\n");
	select_scene(av[1][0], &scene);
	//gen_scene4(&scene);
	f_printf("Generating view, please wait...\n");
	generate_screen(scene.camera, scene.shapes, scene.lights);
	f_printf("Blit\n");
	SDL_UpdateWindowSurface(g_window);
	loop();
	end();
}
