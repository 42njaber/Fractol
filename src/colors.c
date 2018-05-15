/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 19:53:38 by njaber            #+#    #+#             */
/*   Updated: 2018/05/15 21:17:32 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgxns.h"
#include <math.h>

unsigned int			sky(double gradiant, double shift)
{
	const unsigned int color_sky[5] = {0x00FFFFFF, 0x002277FF,
			0x000033AA, 0x00442244, 0x00FFAA00};

	gradiant += shift * 5;
	return (color_gradiant((unsigned int[2]){color_sky[(int)gradiant % 5],
				color_sky[(int)(gradiant + 1) % 5]}, fmod(gradiant, 1)));
}

unsigned int			neon(double gradiant, double shift)
{
	const unsigned int color_neon[5] = {0x00FFFFFF, 0x00FFAAAA,
			0x0033DD33, 0x004422FF, 0x00FF00FF};

	gradiant += shift * 5;
	return (color_gradiant((unsigned int[2]){color_neon[(int)gradiant % 5],
				color_neon[(int)(gradiant + 1) % 5]}, fmod(gradiant, 1)));
}

unsigned int			black_white(double gradiant, double shift)
{
	return (color_gradiant((unsigned int[2]){0x00FFFFFF, 0x00111111},
				(sin(fabs(gradiant * 8 + shift * 4 * M_PI)) + 1) / 2));
}
