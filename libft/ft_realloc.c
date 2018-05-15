/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 20:34:00 by njaber            #+#    #+#             */
/*   Updated: 2018/03/13 01:01:32 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_realloc(void **mem, size_t p_size, size_t n_size)
{
	void	*tmp;

	if ((tmp = (void*)ft_memalloc(n_size)) == NULL)
		return (NULL);
	ft_memcpy(tmp, *mem, ft_umin(p_size, n_size));
	free(*mem);
	*mem = tmp;
	return (mem);
}
