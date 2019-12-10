/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonia <sleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 23:32:56 by sleonia           #+#    #+#             */
/*   Updated: 2019/12/10 09:13:58 by sleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static bool			check_borders(t_map *map)
{
	int				i;

	if (!ft_find_symb_in_str_arr(map->level, '0'))
		return (false);
	if (ft_strchr(map->level[0], '0')
		|| ft_strchr(map->level[map->height - 1], '0'))
		return (false);
	i = 0;
	while (++i < map->height - 1)
	{
		if (map->level[i][0] == '0' || map->level[i][map->width - 1] == '0')
			return (false);
	}
	return (true);
}

static bool			check_symbols_in_map(t_map *map)
{
	int				i;
	int				k;

	i = -1;
	while (map->level[++i])
	{
		k = -1;
		while (map->level[i][++k])
		{
			if ((((int)map->level[i][k] >= T_11 &&
				(int)map->level[i][k] <= T_38)) || (int)map->level[i][k] == 48)
				continue ;
			else
				return (false);
		}
	}
	return (true);
}

static char			*read_file(t_map *map)
{
	char			*str1;
	char			*str2;
	int				fd;
	int				res;

	if ((fd = open(map->name, O_RDONLY)) < 0)
		return (NULL);
	if (get_next_line(fd, &str2) == -1)
		return (NULL);
	map->width = ft_strlen_without_symb(' ', str2);
	while ((res = get_next_line(fd, &str1)) > 0)
		str2 = ft_strjoin_free(str2, str1, 3);
	ft_strdel(&str1);
	if (res == -1)
	{
		ft_strdel(&str2);
		return (NULL);
	}
	close(fd);
	return (str2);
}

static bool			count_height(char *file, t_map *map)
{
	int				i;
	int				file_len;

	i = map->width;
	if ((file_len = ft_strlen_without_symb(' ', file)) == 0)
		return (false);
	while (i <= file_len)
	{
		i += map->width;
		map->height++;
	}
	return (true);
}

static void			fill_map(char *file, t_map **map)
{
	int				i;
	int				k;
	char			*file_without_whitespace;

	i = -1;
	k = 0;
	file_without_whitespace = ft_strnew_without_symb(' ', file);
	(*map)->level =
		(char **)ft_memalloc(sizeof(char *) * ((*map)->height + 1));
	while (++i < (*map)->height)
	{
		(*map)->level[i] =
			ft_strsub(file_without_whitespace, k, (*map)->width);
		k += (*map)->width;
	}
	ft_strdel(&file_without_whitespace);
}

bool				read_map(const char *level_name, t_map *map)
{
	char			*file;

	if (!(file = read_file(map)))
		return (false);
	if (!count_height(file, map))
	{
		ft_strdel(&file);
		return (false);
	}
	if (map->height < 3 || map->width < 3)
	{
		ft_strdel(&file);
		return (false);
	}
	fill_map(file, &map);
	ft_strdel(&file);
	if (!check_symbols_in_map(map))
		return (false);
	if (!check_borders(map))
		return (false);
	return (true);
}
