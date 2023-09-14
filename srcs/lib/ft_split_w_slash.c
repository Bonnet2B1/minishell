/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:04:24 by edelarbr          #+#    #+#             */
/*   Updated: 2022/11/23 17:04:24 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	nextlen(const char *s, size_t i, char c)
{
	size_t	len;

	len = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i])
	{
		len++;
		i++;
	}
	return (len);
}

static size_t	wordcount(const char *s, char c)
{
	size_t	count;
	size_t	i;

	i = 1;
	count = 0;
	while (s[i - 1])
	{
		if (i != 0 && s[i - 1] != c && (s[i] == c || !s[i]))
			count++;
		i++;
	}
	return (count);
}

static char	*nextword(const char *s, size_t *i, char c, size_t len)
{
	char	*cpy;
	size_t	y;

	y = 0;
	while (s[*i] == c)
		(*i)++;
	cpy = malloc(sizeof(char) * (len + 2));
	if (!cpy)
		return (NULL);
	while (len)
	{
		cpy[y++] = s[(*i)++];
		len--;
	}
	cpy[y] = '/';
	cpy[++y] = '\0';
	return (cpy);
}

static char	**freeall_split(char **tab, size_t indice)
{
	size_t	y;

	y = 0;
	while (y <= indice)
	{
		free(tab[y]);
		y++;
	}
	free(tab);
	return (NULL);
}

char	**ft_split_w_slash(const char *s, char c)
{
	size_t	i;
	size_t	y;
	char	**tab;

	i = 0;
	y = 0;
	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (wordcount(s, c) + 1));
	if (!tab)
		return (NULL);
	while (y < wordcount(s, c))
	{
		tab[y] = nextword(s, &i, c, nextlen(s, i, c));
		if (!tab[y])
			return (freeall_split(tab, y));
		y++;
	}
	tab[wordcount(s, c)] = NULL;
	return (tab);
}
