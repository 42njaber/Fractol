/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:12:18 by njaber            #+#    #+#             */
/*   Updated: 2018/03/14 01:54:37 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgxns.h"

void	multiply(t_mat4 m1, t_mat4 m2)
{
	int		i;
	t_mat4	tmp;

	i = -1;
	while (++i < 16)
		tmp[i] = m1[i / 4 * 4] * m2[i % 4] +
				m1[i / 4 * 4 + 1] * m2[i % 4 + 4] +
				m1[i / 4 * 4 + 2] * m2[i % 4 + 8] +
				m1[i / 4 * 4 + 3] * m2[i % 4 + 12];
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
	t_mat4	tmp;

	identity(tmp);
	tmp[0] = cos(v.y / 180 * M_PI) * cos(v.z / 180 * M_PI);
	tmp[1] = -sin(v.z / 180 * M_PI);
	tmp[2] = sin(v.y / 180 * M_PI);
	tmp[4] = sin(v.z / 180 * M_PI);
	tmp[5] = cos(v.x / 180 * M_PI) * cos(v.z / 180 * M_PI);
	tmp[6] = -sin(v.x / 180 * M_PI);
	tmp[8] = -sin(v.y / 180 * M_PI);
	tmp[9] = sin(v.x / 180 * M_PI);
	tmp[10] = cos(v.x / 180 * M_PI) * cos(v.y / 180 * M_PI);
	multiply(tmp, m);
	ft_memcpy(m, tmp, sizeof(t_mat4));
}
