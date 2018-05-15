/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 13:44:55 by njaber            #+#    #+#             */
/*   Updated: 2017/11/30 00:36:32 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count(const char *s, char c)
{
	size_t	ret;
	size_t	i;

	ret = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			ret++;
		i++;
	}
	return (ret);
}

static size_t	wordlength(const char *s, char c)
{
	size_t	ret;

	ret = 0;
	while (s[ret] != c && ret[s] != '\0')
		ret++;
	return (ret);
}

char			**ft_strsplit(const char *s, char c)
{
	char	**ret;
	size_t	word;
	size_t	i;
	size_t	j;

	if (s == NULL)
		return (NULL);
	if ((ret = (char**)ft_memalloc(sizeof(char*) * (count(s, c) + 1))) == NULL)
		return (NULL);
	i = 0;
	word = 0;
	while (word < count(s, c))
	{
		while (s[i] == c)
			i++;
		if ((ret[word] = ft_strnew(wordlength(s + i, c))) == NULL)
			return (NULL);
		j = 0;
		while (j < wordlength(s + i, c))
			(ret[word][j] = s[i + j]) && ++j;
		ret[word][j] = '\0';
		i += j;
		word++;
	}
	return (ret);
}
