/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:12:18 by njaber            #+#    #+#             */
/*   Updated: 2018/05/17 02:22:56 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgxns.h"

void	multiply(t_mat4 m1, t_mat4 m2, int stock_in_m2)
{
	int		i;
	t_mat4	tmp;

	i = -1;
	while (++i < 16)
		tmp[i] = m1[i / 4 * 4] * m2[i % 4] +
				m1[i / 4 * 4 + 1] * m2[i % 4 + 4] +
				m1[i / 4 * 4 + 2] * m2[i % 4 + 8] +
				m1[i / 4 * 4 + 3] * m2[i % 4 + 12];
	if (stock_in_m2)
		ft_memcpy(m2, tmp, sizeof(tmp));
	ft_memcpy(m1, tmp, sizeof(tmp));
}

void	identity(t_mat4 m)
{
	int	i;

	i = -1;
	while (++i < 16)
		if (i % 4 == i / 4)
			m[i] = 1;
		else
			m[i] = 0;
}

void	translate(t_mat4 m, t_vec3 v)
{
	m[3] += v.x * m[15];
	m[7] += v.y * m[15];
	m[11] += v.z * m[15];
}

void	scale(t_mat4 m, t_vec3 v)
{
	m[0] *= v.x;
	m[1] *= v.x;
	m[2] *= v.x;
	m[3] *= v.x;
	m[4] *= v.y;
	m[5] *= v.y;
	m[6] *= v.y;
	m[7] *= v.y;
	m[8] *= v.z;
	m[9] *= v.z;
	m[10] *= v.z;
	m[11] *= v.z;
}

void	rotate(t_mat4 m, t_vec3 v)
{
	v = (t_vec3){v.x / 180 * M_PI, v.y / 180 * M_PI, v.z / 180 * M_PI};
	multiply((t_mat4){cos(v.z), -sin(v.z), 0, 0,
						sin(v.z), cos(v.z), 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1}, m, 1);
	multiply((t_mat4){cos(v.y), 0, -sin(v.y), 0,
						0, 1, 0, 0,
						sin(v.y), 0, cos(v.y), 0,
						0, 0, 0, 1}, m, 1);
	multiply((t_mat4){1, 0, 0, 0,
						0, cos(v.x), -sin(v.x), 0,
						0, sin(v.x), cos(v.x), 0,
						0, 0, 0, 1}, m, 1);
}
