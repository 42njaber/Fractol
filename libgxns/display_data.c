/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 12:10:10 by njaber            #+#    #+#             */
/*   Updated: 2018/06/16 15:10:10 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgxns.h"
#include "mlx.h"

void	display_data_float(t_win *win, char *name, double data, int y)
{
	char	*tmp;

	tmp = ft_printb("%s %.3g", name, data);
	mlx_string_put(win->mlx, win->win, 10, y, 0x777777, tmp);
	free(tmp);
}

void	display_data_vec2(t_win *win, char *name, t_vec2 data, int y)
{
	char	*tmp;

	tmp = ft_printb("%s %g, %g", name, data.x, data.y);
	mlx_string_put(win->mlx, win->win, 10, y, 0x777777, tmp);
	free(tmp);
}

void	display_data_vec3(t_win *win, char *name, t_vec3 data, int y)
{
	char	*tmp;

	tmp = ft_printb("%s %g, %g, %g", name, data.x, data.y, data.z);
	mlx_string_put(win->mlx, win->win, 10, y, 0x777777, tmp);
	free(tmp);
}

void	display_data_str(t_win *win, char *name, char *data, int y)
{
	char	*tmp;

	tmp = ft_printb("%s %s", name, data);
	mlx_string_put(win->mlx, win->win, 10, y, 0x777777, tmp);
	free(tmp);
}
