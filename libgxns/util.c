/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 08:35:05 by njaber            #+#    #+#             */
/*   Updated: 2018/05/15 08:38:20 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgxns.h"
#ifdef AZERTY
# include "azerty.h"
#else
# include "qwerty.h"
#endif

int			get_key_digit(int key_code)
{
	if (key_code == K_0)
		return (0);
	if (key_code == K_1)
		return (1);
	if (key_code == K_2)
		return (2);
	if (key_code == K_3)
		return (3);
	if (key_code == K_4)
		return (4);
	if (key_code == K_5)
		return (5);
	if (key_code == K_6)
		return (6);
	if (key_code == K_7)
		return (7);
	if (key_code == K_8)
		return (8);
	if (key_code == K_9)
		return (9);
	return (-1);
}
