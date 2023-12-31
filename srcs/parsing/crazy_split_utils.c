/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crazy_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelarbr <edelarbr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 21:44:26 by edelarbr          #+#    #+#             */
/*   Updated: 2023/10/04 22:54:55 by edelarbr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isoperator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	take_quote(char **line, int len)
{
	while (line[0][len] && line[1][len] != '0')
		len++;
	return (len);
}

int	take_operator(char **line, int len, char operator)
{
	int	limit;

	if (operator == '<')
		limit = 3;
	else
		limit = 2;
	while (line[0][len] && line[1][len] == '0'
		&& line[0][len] == operator && limit--)
		len++;
	return (len);
}

int	get_len(char **line, int len)
{
	if (ft_isoperator(line[0][len]) && line[1][len] == '0')
		return (len = take_operator(line, len, line[0][len]));
	while ((line[0][len] && line[1][len] == '0'
			&& !ft_iswhitespace(line[0][len]) && !ft_isoperator(line[0][len]))
		|| (line[1][len] && line[1][len] != '0'))
	{
		while (line[0][len] && line[1][len] != '0')
			len++;
		while (line[0][len] && line[1][len] == '0'
			&& !ft_iswhitespace(line[0][len]) && !ft_isoperator(line[0][len]))
			len++;
	}
	return (len);
}

int	get_start(char **line, int start)
{
	while (line[0][start] && line[1][start] == '0'
		&& ft_iswhitespace(line[0][start]))
		start++;
	return (start);
}
