/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 16:43:41 by edelarbr          #+#    #+#             */
/*   Updated: 2023/08/19 16:43:41 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	nextlen(const char *s, size_t i)
{
	size_t	len;
	char	quote;

	quote = 0;
	len = 0;
	while (ft_iswhitespace(s[i]))
		i++;
	while ((quote || !ft_iswhitespace(s[i])) && s[i])
	{
		if (!quote && (s[i] == '\'' || s[i] == '\"'))
			quote = s[i];
		else if (quote == s[i])
			quote = 0;
		len++;
		i++;
	}
	return (len);
}

static size_t	wordcount(const char *s)
{
	size_t	count;
	size_t	i;
	char	quote;

	quote = 0;
	i = 1;
	count = 0;
	while (s[i - 1])
	{
		if (!quote && (s[i - 1] == '\'' || s[i - 1] == '\"'))
			quote = s[i - 1];
		else if (quote && s[i - 1] == quote)
			quote = 0;
		if (!quote && i != 0 && !ft_iswhitespace(s[i - 1])
			&& (ft_iswhitespace(s[i]) || !s[i]))
			count++;
		i++;
	}
	return (count);
}

static char	*nextword(const char *s, size_t *i, size_t len)
{
	char	*cpy;
	size_t	y;

	y = 0;
	while (ft_iswhitespace(s[*i]))
		(*i)++;
	cpy = malloc(sizeof(char) * (len + 1));
	if (!cpy)
		return (NULL);
	while (len)
	{
		cpy[y++] = s[(*i)++];
		len--;
	}
	cpy[y] = '\0';
	return (cpy);
}

static char	**freeall(char **tab, size_t indice)
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

char	**ft_parsing_white_space(const char *s)
{
	size_t	i;
	size_t	y;
	char	**tab;

	i = 0;
	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (wordcount(s) + 1));
	if (!tab)
		return (NULL);
	y = 0;
	while (y < wordcount(s))
	{
		tab[y] = nextword(s, &i, nextlen(s, i));
		if (!tab[y])
			return (freeall(tab, y));
		if (tab[y][0] == '\"' && tab[y][ft_strlen(tab[y]) - 1] == '\"')
			tab[y] = ft_strtrim(tab[y], "\"");
		else if (tab[y][0] == '\'' && tab[y][ft_strlen(tab[y]) - 1] == '\'')
			tab[y] = ft_strtrim(tab[y], "\'");
		y++;
	}
	tab[wordcount(s)] = NULL;
	return (tab);
}
