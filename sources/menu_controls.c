#include "wolf3d.h"

void bg_paralax(int x, int y, t_env *env)
{
	if (x > (WIDTH >> 1))
		env->menu->bg_off[X] = ((x - (WIDTH >> 2)) * 0.02) - 350 * (WIDTH / HEIGHT);
	if (x < (WIDTH >> 1))
		env->menu->bg_off[X] = ((x - (WIDTH >> 2)) * 0.02) - 350 * (WIDTH / HEIGHT);
	if (y > (HEIGHT >> 1))
		env->menu->bg_off[Y] = ((y - (HEIGHT >> 2)) * 0.02) - 400 * (WIDTH / HEIGHT);
	if (y < (HEIGHT >> 1))
		env->menu->bg_off[Y] = ((y - (HEIGHT >> 2)) * 0.02) - 400 * (WIDTH / HEIGHT);
}

void menu_push_buttons(int x, int y, t_env *env)
{
	if (x >= (WIDTH >> 1) - 49 && x <= (WIDTH >> 1) + 335 && y >= (HEIGHT >> 1) - 117 && y <= (HEIGHT >> 1) - 59)
	{
		env->mode = Game;
		// env->mode = Choose;
		renderer(env);
		//draw_chooser(env);
	}
	if (x >= (WIDTH >> 1) - 8 && x <= (WIDTH >> 1) + 335 && 
	y >= (HEIGHT >> 1) - 50 && y <= (HEIGHT >> 1) + 8)
	{
		env->mode = Settings;
		draw_settings(env);
		env->menu->sel_button = 0;
	}
	if (x >= (WIDTH >> 1) - 78 && x <= (WIDTH >> 1) + 335 && y >= (HEIGHT >> 1) + 82 && y <= (HEIGHT >> 1) + 140)
		x_close(env);
}

static void check_button_select(int x, int y, t_env *env)
{
	if (x >= (WIDTH >> 1) - 49 && x <= (WIDTH >> 1) + 335 && 
	y >= (HEIGHT >> 1) - 117 && y <= (HEIGHT >> 1) - 59)
		env->menu->sel_button = '1';
	else if (x >= (WIDTH >> 1) - 8 && x <= (WIDTH >> 1) + 335 && 
	y >= (HEIGHT >> 1) - 50 && y <= (HEIGHT >> 1) + 8)
		env->menu->sel_button = '2';
	else if (x >= (WIDTH >> 1) - 18 && x <= (WIDTH >> 1) + 335 && 
	y >= (HEIGHT >> 1) + 16 && y <= (HEIGHT >> 1) + 74)
		env->menu->sel_button = '3';
	else if (x >= (WIDTH >> 1) - 78 && x <= (WIDTH >> 1) + 335 && 
	y >= (HEIGHT >> 1) + 82 && y <= (HEIGHT >> 1) + 140)
		env->menu->sel_button = '4';
	else
		env->menu->sel_button = 0;
}

void menu_controls(int x, int y, t_env *env)
{
	bg_paralax(x, y, env);
	if (env->mode == Menu)
	{
		check_button_select(x, y, env);
		draw_main_menu(env);
	}
	if (env->mode == Settings)
	{
		settings_controls(x, y, env);
		draw_settings(env);
	}
	// if (env->mode == Choose)
	// 	draw_chooser(env);
}