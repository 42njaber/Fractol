/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 15:23:16 by njaber            #+#    #+#             */
/*   Updated: 2017/11/27 22:21:18 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list*))
{
	t_list	*next;
	t_list	*tmp;
	t_list	*ret;

	if (lst == NULL)
		return (NULL);
	next = NULL;
	if (lst->next != NULL)
	{
		if ((next = ft_lstmap(lst->next, f)) == NULL)
			return (NULL);
	}
	tmp = f(lst);
	if ((ret = ft_lstnew(tmp->content, tmp->content_size)) == NULL)
		return (NULL);
	ret->next = next;
	return (ret);
}
