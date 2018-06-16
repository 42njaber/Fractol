/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 22:58:17 by njaber            #+#    #+#             */
/*   Updated: 2018/06/16 15:11:30 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgxns.h"

unsigned int			color_gradiant(unsigned int *colors, double gradiant)
{
	unsigned int		ret;

	ret = 0;
	ret += (unsigned int)((colors[0] >> 24) * (1 - gradiant) +
			(colors[1] >> 24) * gradiant - 0.5) << 24;
	ret += (unsigned int)(((colors[0] >> 16) & 0xFF) * (1 - gradiant) +
			((colors[1] >> 16) & 0xFF) * gradiant - 0.5) << 16;
	ret += (unsigned int)(((colors[0] >> 8) & 0xFF) * (1 - gradiant) +
			((colors[1] >> 8) & 0xFF) * gradiant - 0.5) << 8;
	ret += (unsigned int)((colors[0] & 0xFF) * (1 - gradiant) +
			(colors[1] & 0xFF) * gradiant - 0.5);
	return (ret);
}
