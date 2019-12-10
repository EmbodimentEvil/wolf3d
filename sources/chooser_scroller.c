/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chooser_scroller.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:26:32 by ahiroko           #+#    #+#             */
/*   Updated: 2019/12/10 09:44:18 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		resset_card_coords(t_env *env)
{
	while (env->menu->cards->id != 0)
		env->menu->cards = env->menu->cards->prev;
	env->menu->cards->pos = 79;
	while (env->menu->cards->id < env->menu->controls->num_of_cards)
	{
		if (!env->menu->cards->next)
			break ;
		env->menu->cards = env->menu->cards->next;
		env->menu->cards->pos = env->menu->cards->prev->pos + 106;
	}
}

void		scrolling(t_env *env, char sign, int old_value)
{
	while (env->menu->cards->id != 0)
		env->menu->cards = env->menu->cards->prev;
	while (env->menu->cards->id < env->menu->controls->num_of_cards)
	{
		if (sign == 0)
			env->menu->cards->pos -= (env->menu->controls->s_pos - old_value) *
				ceil(env->menu->controls->num_of_cards / 7);
		else if (sign == 1)
			env->menu->cards->pos += (old_value - env->menu->controls->s_pos) *
				ceil(env->menu->controls->num_of_cards / 7);
		if (!env->menu->cards->next)
			break ;
		env->menu->cards = env->menu->cards->next;
	}
}

void		move_scroller(int y, t_env *env)
{
	int		temp;
	char	sign;

	temp = env->menu->controls->s_pos;
	env->menu->controls->s_pos = y - 30;
	if (temp < env->menu->controls->s_pos)
		sign = 1;
	else if (temp > env->menu->controls->s_pos)
		sign = 0;
	if (y < 79 + 30)
		env->menu->controls->s_pos = 79;
	if (y > 842 + 30)
		env->menu->controls->s_pos = 842;
	if (temp != env->menu->controls->s_pos)
		scrolling(env, sign, temp);
}

/*
**	What's the logic here? The function will return the map as a structure
**		next you'll have to look at map->level.
**	If it is NULL:
** 		Then I start the reader
** 		Otherwise, I work with him right away
**	Why is that necessary?
**	Not to have to check the card many times
*/

static void	check_validation(const char *map_loc, t_env *env)
{
	t_map	*tmp;

	tmp = find_current_map(map_loc, &env->map);
	if (!tmp->level)
	{
		if (!read_map(map_loc, tmp))
			system("osascript -e \'display notification\" \
This map is not valid!\" with title \"Warning!\"\'");
		else
		{
			env->menu->cards->selected = No;
			load_textures(tmp, env);
			env->mode = Game;	
			change_music(music_flag_1, env->music);
			renderer(env);
		}		
	}
	else
	{
		env->menu->cards->selected = No;
		load_textures(tmp, env);
		env->mode = Game;	
		change_music(music_flag_1, env->music);
		renderer(env);
	}		
}

void		push_scroller(int x, int y, t_env *env)
{
	char	*map_loc;

	check_push_add_buttons(x, y, env);
	if (x >= WIDTH - 100 && x <= WIDTH - 78 &&
		y >= env->menu->controls->s_pos &&
			y <= env->menu->controls->s_pos + 73 &&
				env->menu->controls->scroller_status == 1)
		env->menu->controls->pressed[4] = Yes;
	if (env->menu->controls->num_of_cards > 0)
		if (env->menu->cards->selected == Yes)
		{
			if (!(map_loc = ft_strdup(MAPS_FOLDER)))
				ft_exit(ERROR_MSG);
			if (!(map_loc = ft_strjoin_free(map_loc,
				env->menu->cards->level_name, 1)))
				ft_exit(ERROR_MSG);
			check_validation(map_loc, env);
			if (map_loc)
				free(map_loc);
		}
}
