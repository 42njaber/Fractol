/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 01:35:36 by njaber            #+#    #+#             */
/*   Updated: 2018/05/15 20:06:14 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgxns.h"

t_vec2			c_mult(t_vec2 z1, t_vec2 z2)
{
	return ((t_vec2){z1.x * z2.x - z1.y * z2.y, z1.x * z2.y + z1.y * z2.x});
}

t_vec2			c_pow(t_vec2 z1, int pow)
{
	t_vec2 ret;

	ret = z1;
	while (--pow > 0)
		ret = c_mult(ret, z1);
	return (ret);
}

t_vec2			c_add(t_vec2 z1, t_vec2 z2)
{
	return ((t_vec2){z1.x + z2.x, z1.y + z2.y});
}
