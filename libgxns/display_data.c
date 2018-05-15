/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 12:10:10 by njaber            #+#    #+#             */
/*   Updated: 2018/04/23 18:08:53 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgxns.h"
#include "mlx.h"

void	display_data_float(t_win *win, char *name, double data, int y)
{
	char	*tmp;

	mlx_string_put(win->mlx, win->win, 10, y, 0x777777, name);
	mlx_string_put(win->mlx, win->win, 100, y, 0x777777,
			(tmp = ft_itoa(rint(data))));
	free(tmp);
}

void	display_data_vec2(t_win *win, char *name, t_vec2 data, int y)
{
	char	*tmp;

	mlx_string_put(win->mlx, win->win, 10, y, 0x777777, name);
	mlx_string_put(win->mlx, win->win, 100, y, 0x777777,
			(tmp = ft_itoa(rint(data.x))));
	free(tmp);
	mlx_string_put(win->mlx, win->win, 150, y, 0x777777, ",");
	mlx_string_put(win->mlx, win->win, 170, y, 0x777777,
			(tmp = ft_itoa(rint(data.y))));
	free(tmp);
}

void	display_data_vec3(t_win *win, char *name, t_vec3 data, int y)
{
	char	*tmp;

	mlx_string_put(win->mlx, win->win, 10, y, 0x777777, name);
	mlx_string_put(win->mlx, win->win, 100, y, 0x777777,
			(tmp = ft_itoa(rint(data.x))));
	free(tmp);
	mlx_string_put(win->mlx, win->win, 150, y, 0x777777, ",");
	mlx_string_put(win->mlx, win->win, 170, y, 0x777777,
			(tmp = ft_itoa(rint(data.y))));
	free(tmp);
	mlx_string_put(win->mlx, win->win, 220, y, 0x777777, ",");
	mlx_string_put(win->mlx, win->win, 240, y, 0x777777,
			(tmp = ft_itoa(rint(data.z))));
	free(tmp);
}

void	display_data_str(t_win *win, char *name, char *data, int y)
{
	mlx_string_put(win->mlx, win->win, 10, y, 0x777777, name);
	mlx_string_put(win->mlx, win->win, 100, y, 0x777777, data);
}
